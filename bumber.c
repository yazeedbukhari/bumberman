/* This files provides address values that exist in the system */

#define SDRAM_BASE            0xC0000000
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_CHAR_BASE        0xC9000000

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030

/* VGA colors */
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

/* Constants for animation */
#define BOX_LEN 2
#define NUM_BOXES 8

#define FALSE 0
#define TRUE 1

// Game block (map) definitions:
#define GRASS 0 
#define STONE 1
#define BRICK 2
#define BOMB 3
#define EXPLODE 4
#define PLAYER1 5
#define PLAYER2 6 

// Includes
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Structure definitions
typedef struct {
    int X; // x Location
    int Y; // y location
    int bombRadius; // default 1
    int moveSpeed; // 
    int bombNum; // max bombs player can place at once
    int bombsPlaced; // 
} Player;

// Function definitions: 
void playBumber();

// global variables: 
int mapArray[15][13]{};
// Bumberman code:

volatile int pixel_buffer_start; // global variable

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    int box[NUM_BOXES][5];
    int color[] = {WHITE, YELLOW, RED, GREEN, BLUE, CYAN, MAGENTA, GREY, PINK, ORANGE};

    srand(time(NULL));
    for (int i = 0; i < NUM_BOXES; i++) {
        box[i][0] = rand()%320;
        box[i][1] = rand()%240;
        box[i][2] = -1;
        box[i][3] = -1;

        if (rand()%2 == 0) box[i][2] = 1;
        if (rand()%2 == 0) box[i][3] = 1;

        box[i][4] = color[rand()%10];
    }


    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the 
                                        // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        clear_screen(); //for now

        // code for drawing the boxes and lines
        for (int i = 0; i < NUM_BOXES; i++) {
            draw_box(box[i][0], box[i][1], box[i][4]);

            draw_line(box[i][0], box[i][1], box[(i+1)%NUM_BOXES][0], box[(i+1)%NUM_BOXES][1], box[i][4]);
        }


        // code for updating the locations of boxes

        for (int i = 0; i < NUM_BOXES; i++) {
            
            if (box[i][0] == RESOLUTION_X-BOX_LEN || box[i][0] == 0) {
                box[i][2] *= -1;
            }

            if (box[i][1] == RESOLUTION_Y-BOX_LEN || box[i][1] == 0) {
                box[i][3] *= -1;
            }

            box[i][0] += box[i][2];
            box[i][1] += box[i][3];


        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

void draw_line(x0, y0, x1, y1, color) {
    // is_steep
    int is_steep = (abs(y1-y0) > (abs(x1-x0))) ? TRUE:FALSE;

    int temp;
    if (is_steep == TRUE) {
        //swap(x0, y0)
        temp = x0;
        x0 = y0;
        y0 = temp;

        //swap(x1, y1)
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    else if (x0 > x1) {
        //swap(x0, x1)
        temp = x0;
        x0 = x1;
        x1 = temp;

        //swap(y0, y1)
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -1 * (deltax / 2);

    int y = y0;
    int y_step;

    if (y0 < y1) {
        y_step = 1;
    }
    else {
        y_step = -1;
    }

    for (int x = x0; x <= x1; x++) {
        if (is_steep == TRUE) {
            plot_pixel(y, x, color);
        }
        else {
            plot_pixel(x, y, color);
        }

        error += deltay;
        if (error > 0) {
            y += y_step;
            error -= deltax;
        }
    }

}


void clear_screen() {
    for (int i = 0; i < RESOLUTION_X; i++) {
        for (int j = 0; j < RESOLUTION_Y; j++) {
            plot_pixel(i, j, 0);
        }
    }
}

void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void wait_for_vsync() {
    volatile int * pixel_ctrl_ptr = (int *) 0xFF203020;
    register int status;

    *pixel_ctrl_ptr = 1;

    status = *(pixel_ctrl_ptr + 3);
    while ((status & 0x01) != 0) {
        status = *(pixel_ctrl_ptr + 3);
    }
}

void draw_box(int x, int y, short int color) {
    for (int i = 0; i < BOX_LEN; i++) {
        for (int j = 0; j < BOX_LEN; j++) {
            plot_pixel(x + i, y + j, color);
        }
    }
}

void playBumber() {
    
}
