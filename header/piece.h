//#pragma once

#ifndef PIECE_H
#define PIECE_H

#include<string> // INCLUDE STRING NEEDS TO BE BEFORE SDL2 - Mac user
#include <SDL2/SDL.h>
//#include "Square.h"
using namespace std;

class Piece {
    protected:
        SDL_Texture* gTexture; 
        int owner;
        int numMoves = 0; // certain rules in game are based on whether piece has moved or not
        std::string type; // it will be useful to indicate a type using string

    public: 

        Piece() = default; // default constructor
        // pure virtual
        virtual bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) = 0;
        
        int getOwner() {
            return this->owner;
        }

        SDL_Texture* getTexture() {
            return this->gTexture;
        }

        void incrementMove() {
            ++numMoves;
        } 

        const string name() {
                return type;
        }

        const int moveNum() {
            return numMoves;
        }
};


#endif
