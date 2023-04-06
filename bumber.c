
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
#define GAME_RESOLUTION_X 304
#define GAME_RESOLUTION_Y 240
#define BLOCK_RES_X 19
#define BLOCK_RES_Y 15
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
#define BLOCK_WIDTH 16 // 16x16 block
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

#define PLAYER_WIDTH 16
// 8 pixel wide player
// Function definitions: 
void playBumber();
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void wait_for_vsync();
void drawBlock(int x, int y, int blockType);
void initializePlayer1();
void initializeMap(); 
void drawPlayer(Player player);
void drawBumber();
// global variables: 
int mapArray[BLOCK_RES_X][BLOCK_RES_Y] = {0}; // 304 by 240 in terms of 16 x 16 blocks
int fullMapArray[GAME_RESOLUTION_X][GAME_RESOLUTION_Y] = {0}; // Pixel by pixel
int gameOver = FALSE;
int multiPlayer = TRUE;
int mainMenu = FALSE; // should be true. false for now
int initializeFirst = TRUE; 

// Sprites (images of blocks / player.. etc)

const int grassSprite[16][16] = {
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
    {9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
};

const int stoneSprite[16][16] = {
    {35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953},
    {35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 48567, 35953, 35953},
    {35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953},
    {35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953, 35953},
};

const int playerSprite[16][16] = {
{9610, 9610, 9610, 9610, 9610, 65496, 65496, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
{9610, 9610, 9610, 9610, 9610, 65496, 65496, 65496, 9610, 9610, 9610, 65496, 61669, 61669, 9610, 9610},
{9610, 9610, 9610, 9610, 61669, 61669, 61669, 61669, 61669, 9610, 9610, 9610, 9610, 61669, 61669, 9610},
{9610, 9610, 9610, 61669, 61669, 65496, 65496, 65496, 65496, 61669, 9610, 9610, 9610, 9610, 61669, 9610},
{9610, 9610, 61669, 61669, 65496, 65535, 65535, 61669, 65496, 65496, 61669, 9610, 9610, 9610, 61669, 61669},
{9610, 61669, 61669, 61669, 65496, 61669, 61669, 61669, 65496, 65496, 61669, 9610, 61669, 61669, 61669, 65496},
{9610, 61669, 61669, 61669, 65496, 65496, 65496, 65496, 65496, 65496, 65496, 61669, 61669, 61669, 61669, 65496},
{9610, 61669, 61669, 61669, 61669, 65496, 65496, 65496, 65496, 61669, 65496, 61669, 61669, 61669, 61669, 61669},
{9610, 61669, 61669, 61669, 61669, 65496, 65496, 65496, 65496, 61669, 65496, 61669, 61669, 61669, 61669, 61669},
{9610, 61669, 61669, 61669, 65496, 65496, 65496, 65496, 65496, 65496, 65496, 61669, 61669, 61669, 61669, 65496},
{9610, 61669, 61669, 61669, 65496, 61669, 61669, 61669, 65496, 65496, 61669, 9610, 61669, 61669, 61669, 65496},
{9610, 9610, 61669, 61669, 65496, 65535, 65535, 61669, 65496, 65496, 61669, 9610, 9610, 9610, 61669, 61669},
{9610, 9610, 9610, 61669, 61669, 65496, 65496, 65496, 65496, 61669, 9610, 9610, 9610, 9610, 9610, 9610},
{9610, 9610, 9610, 9610, 61669, 61669, 61669, 61669, 61669, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
{9610, 9610, 9610, 9610, 9610, 65496, 65496, 65496, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
{9610, 9610, 9610, 9610, 9610, 65496, 65496, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610, 9610},
};
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

void drawBlock(int x, int y, int blockType) {
    // functions draws blocks e.g Grass.. etc. Depending on blocktype. 
    int color = 0;
    for (int i = 0; i < BLOCK_WIDTH; i++) {
        for (int j = 0; j < BLOCK_WIDTH; j++) {
            if (blockType == GRASS) {
                color = grassSprite[i][j];
            } else if (blockType == STONE) {
                color = stoneSprite[i][j];
            } else if (blockType == BRICK) {

            }
            plot_pixel(x + i, y + j, color);
            fullMapArray[x + i][y +j] = blockType; 
        }
    }

}

void playBumber() {
    
}

void initializePlayer1() {
    p1.x = 1 * BLOCK_WIDTH; // x Location
    p1.y = 1 * BLOCK_WIDTH; // y location
    p1.bombRadius = 1; // default 1
    p1.bombNum = 1; // max bombs player can place at once
    p1.bombsPlaced = 0; // 
    p1.colour = ORANGE; 
}

void drawPlayer(Player player) {
// take in type player to determine where to draw.
    for (int i = 0; i < PLAYER_WIDTH; i++) {
        for (int j = 0; j < PLAYER_WIDTH; j++) {
            plot_pixel(i + player.x, j + player.y, playerSprite[i][j]);           
        }   
    }
}

void drawBumber() {
    clear_screen(); 
    if (initializeFirst == 1) {
        initializePlayer1();
        initializeMap();
        if (multiPlayer) {
            // initialize player 2
        }

        initializeFirst = FALSE;
    }
    // 304 by 240
    for (int i = 0; i < GAME_RESOLUTION_X; i += BLOCK_WIDTH) {
        for (int j = 0; j < GAME_RESOLUTION_Y; j+= BLOCK_WIDTH) {
            drawBlock(i, j, mapArray[i / BLOCK_WIDTH][j / BLOCK_WIDTH]);
        }
    }
    drawPlayer(p1); 
}

void initializeMap() {
    // everything is grass by default, so we should just add in blocks
    // 
    // initialize borders to be stone
    for (int i = 0; i < BLOCK_RES_X; i++) {
        mapArray[i][0] = STONE;
        mapArray[i][BLOCK_RES_Y - 1] = STONE;
    }
    for (int j = 0; j < BLOCK_RES_Y; j++) {
        mapArray[0][j] = STONE;
        mapArray[BLOCK_RES_X - 1][j] = STONE;
    }    
    for (int i = 2; i < BLOCK_RES_X - 1; i+= 2) {
        for (int j = 2; j < BLOCK_RES_Y - 1; j+= 2) {
            mapArray[i][j] = STONE;
        } 
    }    
}
int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)

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