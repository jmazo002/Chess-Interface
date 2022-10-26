#include<string>
#include <SDL2/SDL.h>
#include <iostream>

#include "header/piece.h"
#include "header/Square.h"
#include "header/Gameboard.h"


const int SCREEN_WIDTH = 616;
const int SCREEN_HEIGHT = 616;


bool init(SDL_Window* &window, SDL_Renderer* &renderer) { // these pointers are passed by reference so this function updates them in main()
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // if the LHS < 0, then SDL has failed to initialize
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;

        success = false;
    }
    else { // create the window
        window = SDL_CreateWindow("REGICIDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
        // ("Window Title Text", Window_Location_X, Window_Location_Y, pixelWidth, pixelHeight, creationFlag)
            // very last argument is the creation flag, "SDL_WINDOW_SHOWN", ensures that window is selected and show the user when it's created (rather than creating minimized)

        if (window == nullptr) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            // implementing a HW renderer?
                // if the window is initialized,
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC); // the renderer will draw to gWindow
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        }
    }

    return success;
}


int main(int argv, char* argc[]) { // remember, main() SPECIFICALLY needs to take these arguements for SDL compatibility
    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gScreenRenderer = nullptr;

    if (!init(gWindow, gScreenRenderer)) { // gWindow and gScreenRenderer are initialized here
        std::cout << "Failed to initialize!" << std::endl;
    }

    else 
    {
        Gameboard* game = new Gameboard(gScreenRenderer); // pass in renderer to constructor
        game->init(); // initialize the gameboard with pieces


        int turnsTaken = 0;
        const int player1 = 1;
        const int player2 = 2;
        bool gameWon = false;


        bool quit = false;
        SDL_Event* event = new SDL_Event; // an event is anything the user does which should produce some response from the program
        Square* toMovePos = nullptr;
            while (!quit) { // the program fundamentally runs within this loop
                while (SDL_PollEvent(event) != 0) { // continously polls user input, SDL_PollEvent checks for any possible user input and writies it to the event object

                    
                    if (turnsTaken % 2 == 0) { // player 1 should
                        quit = game->drawBoard(event, toMovePos, turnsTaken, player1, gameWon);
                    }
                    else {
                        quit = game->drawBoard(event, toMovePos, turnsTaken, player2, gameWon);
                    }
                }
            }
                
            delete event;
            event = nullptr;
            game->close(gWindow);
            
            delete game;

    }
    return 0;
}