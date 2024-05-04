//
// Created by isaia on 11/12/2023.
//

#ifndef TETRIS3_SHAPEO_H
#define TETRIS3_SHAPEO_H
#include "tetris.h"
#include "Tetromino.h"
#include <SFML/Graphics.hpp>

class ShapeO : public Tetromino{
private:

public:
    explicit ShapeO(sf::Vector2f position = {0.f, 0.f})
            : Tetromino(3,3){
        //set the shape type
        _shapeType = SHAPE_O;

        //DEFINE THE MATRIX VALUES
        int blocks[9] = { 0,1,1,
                          0,1,1,
                          0,0,0};
        //set the internal matrix
        setMatrix(blocks);

        //set the screen size, position, and color
        _size = sf::Vector2f (_rows * BLOCK_SIZE, _columns * BLOCK_SIZE);
        _position = position;
        _fillColor = sf::Color(YELLOW);
    }// default constructor
};// class ShapeO


#endif //TETRIS3_SHAPEO_H