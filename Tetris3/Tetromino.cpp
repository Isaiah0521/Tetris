//file: Tetromino.h
// class: COP PROGRAMMING II
//BY :Isaiah Herard
// desc:Header file for an abstract shape representing one of the shapes is a Tetris Game
// Each shapes is made of up o fmultiple rectangles used to display the shape;
//Internally the Tetromino maintains a Matrix of 0's and 1's to represent where
// graphical shapes should be drawn, based on the top-left corner of this shape.
#include "Tetromino.h"
#include <sstream>

Tetromino::Tetromino() {
    _shapeType = SHAPE_NONE;
    //all other properties are class objects with their own default constructors

}
Tetromino::Tetromino(int rows, int columns)
        :Matrix{rows, columns}{
    _shapeType = SHAPE_NONE;
}

Tetromino::Tetromino(int rows, int columns, int *blocks)
        : Matrix{rows, columns, blocks} {
    _shapeType = SHAPE_NONE;
    // all ther properties are class objects with their own default constructors

}
/**
 * draw the Tetromino by going through the Matrix and
 * creating a RectangleShape, sizing, positioning and
 * filling its color, fo rany cells with a 1
 * @param window - target window to draw on
 */
void Tetromino::draw(sf::RenderWindow &window) {
    // calculate block size relative to size of
    //Tetromino and Matrix rows and Columns
    sf::Vector2f  blockSize { _size.x / _columns,
                              _size.y / _rows };

    //start block position at top left of Tetromino
    sf::Vector2f blockPos = _position;
    for (int row=0; row <_rows; ++row){
        blockPos.x = _position.x;

        for (int col = 0; col < _columns; ++col){
            // see if cell call in Matrix has a 1 in it
            if(hasBlock(row,col)){
                // create temp block, position, and color it
                sf::RectangleShape block{blockSize};
                block.setPosition(blockPos);
                block.setFillColor(_fillColor);
                window.draw(block);
            }
            blockPos.x += blockSize.x;
        }// for each column

        blockPos.y += blockSize.y;
    }

}// end draw
/**
 * Rotate this shape counter-clockwise 90 degrees
 */

void Tetromino::rotate() {
    anticlockwise();
}// end rotate
/**
* @return string representation of the matrix
*/
std::string Tetromino::toString() {
    std::stringstream  ssShape;
    ssShape << "Tetromino: \n";
    ssShape << +"Size: (" << int(_size.x) << "," << int(_size.y) << ")\n";
    ssShape << + "Position: (" << int(_position.x)<< ","<< int(_position.y) << ")\n";
    ssShape << +"Color: (" << int(_fillColor.r) << "," << int(_fillColor.g) << "," << int(_fillColor.b) << ")\n";
    ssShape << Matrix::toString() << std::endl;

    return ssShape.str();
}
/**
 * Move a Tetromino one block left, right, or down. No collision
 * checking is dne here, so this should only be called if it is
 * possible to mve in the direction given
 * @param direction - move shae in given direction
 */
void Tetromino::move(Tetromino::Movement direction){
    switch(direction){
        case MoveLeft:
            _position.x -= _size.x / _columns;
            break;
        case MoveRight:
            _position.x += _size.x / _columns;
            break;
        case MoveDown:
            _position.y += _size.y / _rows;
    }
}//end move
