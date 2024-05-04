//
// Created by isaia on 11/12/2023.
//

#ifndef TETRIS3_SHAPEI_H
#define TETRIS3_SHAPEI_H
#include "tetris.h"
#include "Tetromino.h"
#include <SFML/Graphics.hpp>

class ShapeI : public Tetromino{
private:

public:
    explicit ShapeI(sf::Vector2f position = {0.f, 0.f})
            : Tetromino(4,4){
        //set the shape type
        _shapeType = SHAPE_I;

        //DEFINE THE MATRIX VALUES
        int blocks[16] = { 0,1,0,0,
                           0,1,0,0,
                           0,1,0,0,
                           0,1,0,0};
        //set the internal matrix
        setMatrix(blocks);

        //set the screen size, position, and color
        _size = sf::Vector2f (_rows * BLOCK_SIZE, _columns * BLOCK_SIZE);
        _position = position;
        _fillColor = sf::Color(LIGHT_BLUE);
    }// default constructor
};// class ShapeZ


#endif //TETRIS3_SHAPEI_H
