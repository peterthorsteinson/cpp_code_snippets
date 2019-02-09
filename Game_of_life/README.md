# The Game of Life 
 
- The Game of Life is a cellular automaton created by John Conway.
- The game is played on a grid of cells that each contain a 0 or a 1 value, which defines the state of the game.
- The program sets the initial game state and then follows certain rules to evolve through subsequent game states.

## The Rules: 

- A live cell with less than two live neighbors dies.
- A live cell with two or three live neighbors lives.
- A live cell with more than three neighbors dies.
- A dead cell with three live neighbors becomes live 

## The Input File

A generation consists of these rules being applied to every cell of the current game state, to generate the next game state. 
The initial game state is read in from a file (such as the provided sample input file named input.bin).
The file must adhere to the following convention: 
 
- The first byte is the length of the grid.
- The second byte is the width of the grid.
- The remaining bytes are only 0s or 1s and correspond to a dead or live cell.

This means that for an M x N size grid the size of the file should be (M x N) + 2 bytes.
So that the grid may be printed on a terminal screen we will need to limit grid size appropriately.
The file name is passed to the program as a command-line parameter.

NOTE: The provided sample input file named input.bin is binary (not ascii or unicode), so it must be viewed in a hex editor to see the data contents. The provided input.bin file contains 10 and 10 for the first 2 bytes, followed by 100 bytes that each contain a 0 or a 1. If you want to try editing your own input file, you would have to edit it in a hex editor yourself.

