//
// Created by isaia on 11/12/2023.
//

#ifndef TETRIS3_SHAPET_H
#define TETRIS3_SHAPET_H


class ShapeT : public Tetromino{
private:

public:
    explicit ShapeT(sf::Vector2f position = {0.f, 0.f})
            : Tetromino(3,3){
        //set the shape type
        _shapeType = SHAPE_T;

        //DEFINE THE MATRIX VALUES
        int blocks[9] = { 0,0,0,
                          1,1,0,
                          0,1,1};
        //set the internal matrix
        setMatrix(blocks);

        //set the screen size, position, and color
        _size = sf::Vector2f (_rows * BLOCK_SIZE, _columns * BLOCK_SIZE);
        _position = position;
        _fillColor = sf::Color(MAGENTA);
    }// default constructor
};// class ShapeZ


#endif //TETRIS3_SHAPET_H
