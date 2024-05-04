//
// Created by isaia on 11/12/2023.
//

#ifndef TETRIS3_TETRISBOARD_H
#define TETRIS3_TETRISBOARD_H
#include "tetris.h"
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include <random>
class TetrisBoard {
private:
    bool _canMoveShape(Tetromino::Movement direction) {
        bool canMove = true;
        //move a copy of the current cell
        sf::Vector2i tempCell = _currentCell;

        switch (direction) {
            case Tetromino::MoveLeft:
                if (_currentCell.x < 0)
                    canMove = false;
                else
                    tempCell.x -= 1;
                break;
            case Tetromino::MoveRight: //need +1 or bar (I) shape
                if (_currentCell.x + _currentShape->getColumns() > GAME_COLUMNS + 1)
                    canMove = false;
                else
                    tempCell.x += 1;
                break;
            case Tetromino::MoveDown:
                if (_currentCell.y < 0) {
                    canMove = false;
                } else {
                    tempCell.y -= 1;
                }
        }// direction
        //declare temp shape so default constructor is called to
        Tetromino tempShape;// initialize empty shape before copy

        //make a copy of the current shape to temp shape
        tempShape = *_currentShape;

        //used to indicate if current block in grid is filled of outside walls
        bool filled{};

        //check if temp shape at ew temp cell location has any collision with filled cells
        for (int row = 0; row < tempShape.getRows() && canMove; ++row) {

            for (int column = 0; column < tempShape.getColumns() && canMove; ++column) {
                if (tempCell.x + column < 0 ||
                    tempCell.x + column >= GAME_COLUMNS ||
                    tempCell.y - row < 0) {
                    filled = true;
                } else {
                    filled = _cells[tempCell.y - row][tempCell.x + column].filled;
                }
                //check for collision between temp shape and grid cell
                if (filled and tempShape.hasBlock(row, column)) {
                    canMove = false;
                }

            }// each column

        }// each row

        return canMove;
    }//can move shape

    struct FrameCounters {
        int newShapeRate;
        int newShape;
    };
    FrameCounters _counters;//track and adjust game delays
    struct GridCell {
        bool filled;
        sf::RectangleShape block;
    };

    // grid of cells by rows and column
    GridCell _cells[GAME_ROWS][GAME_COLUMNS];

    //current and next shape
    Tetromino *_currentShape;
    Tetromino *_nextShape;

    //top/left row/column of grid for curent shape
    sf::Vector2i _currentCell;

    //properties for generating random numbers to select
    // the next Tetromino at random
    // randomDevice is a seed for the generator
    //uses a merseene_twister henerator engine
    // produces a uniform integer distribution
    std::random_device _randDevice;
    std::mt19937 _randGenerator;
    std::uniform_int_distribution<> _randDistribution;

    void nextShape(); // calculate next random shape

    void lockShape();

public:
    TetrisBoard();

    ~TetrisBoard();

    bool update(KeyPressedState input[]);

    void render(sf::RenderWindow &window);
};


#endif //TETRIS3_TETRISBOARD_H

