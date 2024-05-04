//
// Created by isaia on 11/12/2023.
//

#ifndef TETRIS3_TETRIS_H
#define TETRIS3_TETRIS_H
#include <SFML/GRAPHICS.hpp>
// The number of rows and columns that make up the grid
const int GAME_ROWS = 21;
const int GAME_COLUMNS = 10;

const int FPS = 30;  // how many updates frame per seond
const int FRAME_RATE_MS = (1.f / float(FPS) * 1000.f); // per millisecond

const int FRAMES_NEW_SHAPE = 45; // DEFAULT RATE TO SHOW NEXT SHAPE


//SIZE OF A SQUARE BLOCK (WIDH AND HEIGHT) OF EACH BLOCK IN THE
//Tetris gameboard grid and individual blocks of a Tetromino shape
const int BLOCK_SIZE = 30;

const int WIN_WIDTH = GAME_COLUMNS * BLOCK_SIZE + (2 * BLOCK_SIZE); // 1 BLOCK ON LEFT AND RIGHT OF GAME BOARD
const int WIN_HEIGHT = GAME_ROWS *BLOCK_SIZE + (2 * BLOCK_SIZE); //1 BLOCK ON TOP AND BOTTOM OF GAME BOARD

const int GRID_TOP = BLOCK_SIZE;
const int GRID_LEFT = BLOCK_SIZE;

const int START_CELL_COLUMN = 3;
const int START_CELL_ROW = 20;

const sf::Color BACKGOUND_COLOR = sf::Color::Black;
const sf::Color GRID_COLOR = sf::Color(0xD3, 0xD3,0xD3, 50);// light grey 50/255 `20% Opacity

struct KeyPressedState{ //maintain state of each input key access frames
    bool prior;     //state of key in prior frame: Pressed = true
    bool current;       //state of key for this frame: Pressed = true
};
#endif //TETRIS3_TETRIS_H
