//#pragma once

#ifndef SQUARE_H
#define SQUARE_H

#include<string>
#include <SDL2/SDL.h>
#include "Piece.h"

enum ButtonState {NORMAL  = 0, HOVER = 1, PRESSED = 2};

// regard Squares as buttons
    // in the event a button is pressed:
        // if the Square contained a piece, the player wants to move the piece
            // if the player then clicks another Square, that is the destination for the piece
    // if the Square did not contain a piece, ignore

class Square {
    private:
        Piece* heldPiece; // will point to the piece that the square currently contains

        int gridX;
        int gridY;

        SDL_Rect* rect; //SDL_Rect(int X, int Y, int height, int width);


    public:
        Square(int x, int y, int gridX, int gridY); // constructor takes
        void populateSquare(Piece* piece);


        // getters
        Piece* getHeldPiece();
        SDL_Rect* getRect();

        int getGridX();
        int getGridY();


};

#endif
