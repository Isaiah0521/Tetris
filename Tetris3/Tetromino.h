//file: Tetromino.h
// class: COP PROGRAMMING II
//BY :Isaiah Herard
// desc:Header file for an abstract shape representing one of the shapes is a Tetris Game
// Each shapes is made of up o fmultiple rectangles used to display the shape;
//Internally the Tetromino maintains a Matrix of 0's and 1's to represent where
// graphical shapes should be drawn, based on the top-left corner of this shape.
#include <SFML/Graphics.hpp>
#include "Matrix.h"
# include <string>

#ifndef TETRIS3_TETROMINO_H
#define TETRIS3_TETROMINO_H




class Tetromino : public Matrix {
public:
    //colors that can be used for each of the shape
    static const unsigned int LIGHT_BLUE = 0xADD8E6FF;
    static const unsigned int DARK_BLUE = 0x00008BFF;
    static const unsigned int ORANGE = 0xFFA500FF;
    static const unsigned int YELLOW = 0xFFFF00FF;
    static const unsigned int GREEN  = 0x00FF00FF;
    static const unsigned int RED = 0xFF0000FF;
    static const unsigned int MAGENTA  = 0xFF00FFFF;

    //known Tetromino shape types
    enum ShapeType {
        SHAPE_NONE = -1,
        SHAPE_I,
        SHAPE_J,
        SHAPE_L,
        SHAPE_O,
        SHAPE_S,
        SHAPE_T,
        SHAPE_Z,
        SHAPE_COUNT
    };
    //shape movement constants
    enum Movement{
        MoveNone,
        MoveLeft,
        MoveRight,
        MoveDown
    };
protected:
    ShapeType _shapeType;

    sf::Vector2f _size;   //(width, height}
    sf::Vector2f  _position;// (left, top?)
    sf::Color _fillColor;
public:
    //Constructors
    //--------------------------------------------------------------------
    Tetromino();// default constructors
    Tetromino(int rows, int columns);
    Tetromino(int rows, int columns, int *blocks);

    //Accessors
    //-------------------------------------------------------------
    ShapeType getShapeType(){
        return _shapeType;
    }
    sf::Vector2f  getSize(){return _size;}
    void setSize(sf::Vector2f size){_size = size; }

    sf::Vector2f getPosition(){return _position; }
    void setPosition(sf::Vector2f position) {_position = position; }

    sf::Color getFillColor(){return  _fillColor; }
    void setFillColor(sf::Color fillColor){ _fillColor = fillColor; }
    //Methods
    //--------------------------------------------------
    void draw(sf::RenderWindow & window);

    void rotate();

    void move(Movement direction);

    std::string toString();
};


#endif //TETRIS3_TETROMINO_H
