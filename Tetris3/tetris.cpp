// file:tetris2.cpp
//class:Cop 3003 Programming II
//BY: Isaiah Herard
//description: main application
//----------------------------------------------------
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include <iostream>
#include "tetris.h"
#include "TetrisBoard.h"
//function declarations (prototypes)
//-----------------------------------------------------------
bool processEvents(sf::RenderWindow & window, KeyPressedState input[]);
bool update(KeyPressedState input[], TetrisBoard & board);
void render(sf::RenderWindow & window, TetrisBoard & board);



//function definitions
//---------------------------------------------------------------
int main() {
    //create the game window width x height with title
    sf::RenderWindow window {sf::VideoMode{WIN_WIDTH, WIN_HEIGHT}, "Tetris"};

    //game board grid for the Tetris game
    TetrisBoard gameboard;
    //keyboard state handing
    KeyPressedState keyStates[sf::Keyboard::KeyCount] = {0};



    //update frame timing
    //--------------------------------------------------------------------
    sf::Clock frameTimer; //frame rate timer
    int lag{100}; // cumulative lag time each frame

    //main game loop
    //----------------------------------------------------------------------
    bool gameover = false;


    //main game loop
    while(!gameover){
        lag += frameTimer.restart().asMilliseconds();

        gameover = processEvents(window, keyStates);
        // wait until we get to a frame boundary to update
        while( lag >= FRAME_RATE_MS){

            gameover = update(keyStates, gameboard);

            lag -= FRAME_RATE_MS;// reduce lag by 1 frame
        }

        render(window, gameboard);

    }//end of main game loop

    //clean up the main window
    window.close();

    return 0;
}// end of main

/**
* process windows and keyboard events
 * @param window - reference to the main window
 * @param input - prior and current state of each keyboard key
 * @return true = window closing
*/
bool processEvents(sf::RenderWindow & window, KeyPressedState input[]) {
    bool closing = false;

    sf::Event event;
    while (window.pollEvent(event))
    {

        //"close requested" event : return closing true
        if( event.type == sf::Event::Closed)
            closing = true;// return closing true
        else if (event.type == sf::Event::KeyReleased){
            if(!input[event.key.code].prior){
                //set current and prior state on
                //will be turned off in update
                input[event.key.code].current = true;  // detected this loop
                input[event.key.code].prior = true;  //ignore next loop
            }
        }
    }
    //check for keyboard events
    //only watching for key being released

    return closing;
}// end  process events

/**
 * draw shapes on the main window
 * @param input - keyboard input
 * @param board - Tetris game board
 * @return true if game should end
 */

bool update(KeyPressedState input[],TetrisBoard & board){
    bool endgame = false;

    //update objects on the gameboard
    endgame = board.update(input);

    return endgame;

}//end update
/**
 * process key nput for update frames
 * @param input - current key states
 * @param key - check state of particular key
 * @return true if key is in a pressed state
 */



/**
 * draw shapes on the main window
 * @param window - reference to the main window
 * @param board - main gameboard
 */
void render(sf::RenderWindow & window, TetrisBoard & board){

    window.clear(BACKGOUND_COLOR);

    //Call draw method of shapes
    board.render(window);

    window.display();

}// end render