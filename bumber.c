
#define BOARD                 "DE1-SoC"

/* Memory */
#define DDR_BASE              0x00000000
#define DDR_END               0x3FFFFFFF
#define A9_ONCHIP_BASE        0xFFFF0000
#define A9_ONCHIP_END         0xFFFFFFFF
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_ONCHIP_END       0xC803FFFF
#define FPGA_CHAR_BASE        0xC9000000
#define FPGA_CHAR_END         0xC9001FFF

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define JP1_BASE              0xFF200060
#define JP2_BASE              0xFF200070
#define PS2_BASE              0xFF200100
#define PS2_DUAL_BASE         0xFF200108
#define JTAG_UART_BASE        0xFF201000
#define JTAG_UART_2_BASE      0xFF201008
#define IrDA_BASE             0xFF201020
#define TIMER_BASE            0xFF202000
#define AV_CONFIG_BASE        0xFF203000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define AUDIO_BASE            0xFF203040
#define VIDEO_IN_BASE         0xFF203060
#define ADC_BASE              0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE        0xFF709000
#define HPS_TIMER0_BASE       0xFFC08000
#define HPS_TIMER1_BASE       0xFFC09000
#define HPS_TIMER2_BASE       0xFFD00000
#define HPS_TIMER3_BASE       0xFFD01000
#define FPGA_BRIDGE           0xFFD0501C

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) CPU interface(s) */
#define MPCORE_GIC_CPUIF      0xFFFEC100    // PERIPH_BASE + 0x100
#define ICCICR                0x00          // offset to CPU interface control reg
#define ICCPMR                0x04          // offset to interrupt priority mask reg
#define ICCIAR                0x0C          // offset to interrupt acknowledge reg
#define ICCEOIR               0x10          // offset to end of interrupt reg
/* Interrupt controller (GIC) distributor interface(s) */
#define MPCORE_GIC_DIST       0xFFFED000    // PERIPH_BASE + 0x1000
#define ICDDCR                0x00          // offset to distributor control reg
#define ICDISER               0x100         // offset to interrupt set-enable regs
#define ICDICER               0x180         // offset to interrupt clear-enable regs
#define ICDIPTR               0x800         // offset to interrupt processor targets regs
#define ICDICFR               0xC00         // offset to interrupt configuration regs

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

#define FALSE   0
#define TRUE    1

// Game block (map) definitions:
#define GRASS   0 
#define STONE   1
#define BRICK   2
#define BOMB    3
#define EXPLODE 4
#define PLAYER1 5
#define PLAYER2 6 
#define BLOCK_WIDTH 10 // 10 by 10 block
// Game State Definitions
#define HOME    0
#define ONEP    1
#define TWOP    2
#define OVER    3

// Includes
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Structure definitions
typedef struct {
    int x; // x Location
    int y; // y location
    int bombRadius; // default 1
    int moveSpeed; // 
    int bombNum; // max bombs player can place at once
    int bombsPlaced; // 
    int colour; // colour of player
} Player;

Player p1; // at most we have 2 players
Player p2; 
#define PLAYER_WIDTH 20
// 8 pixel wide player
// Function definitions: 
void playBumber();

// global variables: 
int mapArray[15][13] = {0};
int gameOver = FALSE;
int multiPlayer = TRUE;
int mainMenu = FALSE; // should be true. false for now
int initializeFirst = TRUE; 
// Bumberman code:

volatile int pixel_buffer_start; // global variable

void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void clear_screen() {
    for (int i = 0; i < RESOLUTION_X; i++) {
        for (int j = 0; j < RESOLUTION_Y; j++) {
            plot_pixel(i, j, 0);
        }
    }
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

void initializePlayer1() {
    p1.x = 10; // x Location
    p1.y = 10; // y location
    p1.bombRadius = 1; // default 1
    p1.bombNum = 1; // max bombs player can place at once
    p1.bombsPlaced = 0; // 
    p1.colour = ORANGE; 
}

void drawPlayer(Player player) {
// take in type player to determine where to draw.
    for (int i = player.x; i < PLAYER_WIDTH; i++) {
        for (int j = player.y; j < PLAYER_WIDTH; j++) {
            plot_pixel(i, j, player.colour);           
        }   
    }
}

void drawBumber() {
    if (initializeFirst == 1) {
        initializePlayer1();
        if (multiPlayer) {
            // initialize player 2
        }

        initializeFirst = FALSE;
    }
    // 320 by 240
    for (int i = 0; i < RESOLUTION_X; i++) {
        for (int j = 0; j < RESOLUTION_Y; j++) {
            plot_pixel(i, j, GREEN);
        }
    }
    drawPlayer(p1); 
}

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    int color[] = {WHITE, YELLOW, RED, GREEN, BLUE, CYAN, MAGENTA, GREY, PINK, ORANGE};

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

        if (multiPlayer == 1) {
        drawBumber();

        }
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}