# Bumberman
Bomberman game by Yazeed Bukhari and Alan Bu for ECE243 final project.
Made for DE1-SoC FPGA board and outputs the game using VGA ports.

Can be simulated on CPULator: https://cpulator.01xz.net/?sys=arm-de1soc. 
Simulation is significantly slower however, and "BOMB_TIMER" in the code needs to be changed to 9 - 15 seconds
To play, copy and paste the code onto CPULator and set the language to "C". Click "compile and load" (F5), followed by "continue" (F3).
Input can be entered using the PS/2 keyboard found by scrolling on the right, under "devices." Output will be displayed on the VGA. 

In multiplayer:
The goal is to blow up the other player
The controls for player 1 (red) are 'W','A','S','D' to move, and 'C' to place a bomb. 
The controls for player 2 (blue) are the arrow keys to move, and '/' to place a bomb. 
Power ups spawn randomly, up to 3 spawned at once. There are 3 different power ups: increase in maximum bombs that can be placed down at once, increase in bomb radius, and increase in movement speed. 

In single player:
The goal is to blow up the blue character
The controls for the player (red) are 'W','A','S','D' to move, and 'C' to place a bomb. 
Power ups can be spawned by pressing a switch on the DE1-SoC board. 
