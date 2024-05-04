//
// Created by isaia on 11/12/2023.
//

#include "TetrisBoard.h"
#include "ShapeI.h"
#include "ShapeJ.h"
#include "ShapeL.h"
#include "ShapeO.h"
#include "ShapeS.h"
#include "ShapeT.h"
#include "ShapeZ.h"
#include <iostream>
bool isKeyPressed(KeyPressedState input[], sf::Keyboard::Key key);
/**
 * Default constructor setups up the gameboard
 */
TetrisBoard::TetrisBoard() {

    //initialize frame counters
    _counters = {FRAMES_NEW_SHAPE, 0};

    //set up the gameboard grid block
    //----------------------------------------------

    //position and size of grid block
    sf::Vector2f position{GRID_LEFT, GRID_TOP}; // SCREEN POSITION
    sf::Vector2f  size{BLOCK_SIZE, BLOCK_SIZE}; // SCREEN SIZE (PIXELS

    //CREATE A TEMP BLOCK SHAPE TO UPDATE THE GRID CELLS
    sf::RectangleShape block{size};
    block.setFillColor(BACKGOUND_COLOR);
    block.setOutlineColor(GRID_COLOR);
    block.setOutlineThickness(-1.f);

    //populate the game board grid with block shapes
    for (int row = GAME_ROWS - 1; row >= 0; --row){
        for (int col = 0; col < GAME_COLUMNS; ++col){
            block.setPosition(position);// set screen position of block



            _cells[row][col] = {false, block}; //copy shae to grid

            position.x += size.x; // move block right 1 cell
        }// columns left to right
        position.x = GRID_LEFT; // rest block left to left side of grid
        position.y += size.y; // move block down to next row of grid

    }// rows from top down to bottom (0)

    // initialize random number generation
    //---------------------------------------
    _randGenerator = std::mt19937(_randDevice());// see the generator engine
    _randDistribution = std::uniform_int_distribution<>(Tetromino::ShapeType::SHAPE_NONE + 1,
                                                        Tetromino::ShapeType::SHAPE_COUNT - 1);
    // initialize current and next shape properties
    //-----------------------------------------------------------------
    _currentShape = nullptr;
    _nextShape = nullptr;
    _currentCell = sf::Vector2i{0,0};

    //get the next shape
    nextShape();

}// default constructor

/**
 * Destructor cleans up gameboard objects
 */
TetrisBoard::~TetrisBoard() {
    delete _currentShape;
    _currentShape = nullptr;

    delete _nextShape;
    _nextShape = nullptr;
}

bool TetrisBoard::update(KeyPressedState *input) {
    bool endgame = false;

    if(_currentShape){
        if(isKeyPressed(input, sf::Keyboard::Key::Space)){
            _currentShape->rotate();
        }

        if(isKeyPressed(input, sf::Keyboard::Key::A)){
            if(_canMoveShape(Tetromino::Movement::MoveLeft)) {
                _currentShape->move(Tetromino::Movement::MoveLeft);
                _currentCell.x -= 1;
            }

        }
        else if(isKeyPressed(input, sf::Keyboard::Key::D)){
            if(_canMoveShape(Tetromino::Movement::MoveRight)) {
                _currentShape->move(Tetromino::Movement::MoveRight);
                _currentCell.x += 1;
            }
        }

        if(isKeyPressed(input, sf::Keyboard::Key::S)){
            if(_canMoveShape(Tetromino::Movement::MoveDown)) {
                _currentShape->move(Tetromino::Movement::MoveDown);
                _currentCell.y -= 1;
            }
        }
        if(!_canMoveShape(Tetromino::Movement::MoveDown)){
            lockShape();
            delete _currentShape;
            _currentShape = nullptr;
        }

        if(isKeyPressed(input, sf::Keyboard::Key::Enter)){
            std::cout << _currentShape->toString() <<std::endl;
        }


    }
    else{// no current shape
        //count frames until time to show next shape
        if(_counters.newShape < _counters.newShapeRate){
            _counters.newShape++; // increase frame counter
        }
        else {//show next shape
            _counters.newShape = 0;// reset counter
            _currentShape = _nextShape;//copy next to current
            nextShape();// get next shape
        }
    }
    return  endgame;
}// update

/**
 * draw game objects on the window
 * @param window - main game window
 */
void TetrisBoard::render(sf::RenderWindow &window) {
    // draw the grid
    for (int row = 0; row < GAME_ROWS; ++row){
        for(int col = 0; col < GAME_COLUMNS; ++col){
            window.draw(_cells[row][col].block);
        }// each column
    }//each row
    // draw current shape if we have one
    if(_currentShape){
        _currentShape ->draw(window);
    }

}// render

//Private methods
//---------------------------------------------------------

/**
* Randomly selects the next shape to show
*/
void TetrisBoard::nextShape(){
    //reset current shape cell to top center
    _currentCell = sf::Vector2i (START_CELL_COLUMN, START_CELL_ROW);

    //calculate starting screen position
    float x =(_currentCell.x + 1) * BLOCK_SIZE;
    float y = (GAME_ROWS - _currentCell.y) * BLOCK_SIZE;
    sf::Vector2f  position{x, y};

    //generate random shape type
    auto nextType = static_cast<Tetromino::ShapeType>(_randDistribution(_randGenerator));

    //generate a shape for next Shape
    switch(nextType){
        case Tetromino::ShapeType::SHAPE_I:
            _nextShape = new ShapeI(position);
            break;
        case Tetromino::ShapeType::SHAPE_J:
            _nextShape = new ShapeJ(position);
            break;
        case Tetromino::ShapeType::SHAPE_L:
            _nextShape = new ShapeL(position);
            break;
        case Tetromino::ShapeType::SHAPE_O:
            _nextShape = new ShapeO(position);
            break;
        case Tetromino::ShapeType::SHAPE_S:
            _nextShape = new ShapeS(position);
            break;
        case Tetromino::ShapeType::SHAPE_T:
            _nextShape = new ShapeT(position);
            break;
        case Tetromino::ShapeType::SHAPE_Z:
            _nextShape = new ShapeZ(position);
            break;
    }// switch type

}// next shape
bool isKeyPressed(KeyPressedState input[], sf::Keyboard::Key key){
    bool pressed = false;
    //check if key was pressed to rotate the shape
    if(input[key].prior){
        //this is a current key press for this frame
        if (input[key].current){
            pressed = true;
            //turn off the current flag to indivate we processed it
            input[key]. current = false;
        }
        else{// we were skipping a frame
            //turn of the prior flag to indicate we process it
            input[key].prior = false;
        }
    }
    return pressed;

}// is key pressed
void TetrisBoard::lockShape(){
    for (int row = 0; row < _currentShape->getRows(); ++row){
        for (int column = 0; column < _currentShape ->getColumns();++column){
            if(_currentCell.x + column >= 0||
            _currentCell.x + column <= (GAME_COLUMNS - 1) ||
            _currentCell.y - row >= 0){
             if (_currentShape->hasBlock(row, column)){
                 _cells[_currentCell.y - row][_currentCell.x + column].block.setFillColor(_currentShape->getFillColor());
                 _cells[_currentCell.y - row][_currentCell.x + column].filled = true;
             }
            }

        }//each shape
    }//each row
}//lockShape