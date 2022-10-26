#include "../header/Knight.h"

Knight::Knight(SDL_Renderer* r, int playerID) { // constructor should load the appropriate texture based on team
    SDL_Surface* gImage = nullptr;
    
    if (playerID == 1) { // player 1's pieces load white assets
        gImage = SDL_LoadBMP("assets/whiteKnightScaled.bmp");        
    }
    else { // player 2's pieces load black assets
        gImage = SDL_LoadBMP("assets/blackKnightScaled.bmp"); // images need to be loaded into surfaces specifically, not textures
    }
                                                        // this this surface can be converted into a texture
    this->gTexture = SDL_CreateTextureFromSurface(r, gImage);
    SDL_FreeSurface(gImage);

    this->type = "Knight";

    this->owner = playerID;
}

Knight::~Knight() {
    SDL_DestroyTexture(this->gTexture);
}

bool Knight::validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) // piece can move in any direction as long as it is not blocked by a piece
{   
    int x = destinationX - currentX;
    int y = destinationY - currentY;

    if(getOwner() == 1) {
        if( (x == 1 || x == -1) && (y == 2 || y == -2) && (piece == nullptr || piece->getOwner() == 2 )) {

            return true;
        }

        else if( (x == 2 || x == -2) && (y == 1 || y == -1) && (piece == nullptr || piece->getOwner() == 2 )) {
        
            return true;
        }

    }

    else if(getOwner() == 2) {
         if( (x == 1 || x == -1) && (y == 2 || y == -2) && (piece == nullptr || piece->getOwner() == 1 )) {

            return true;
        }

        else if( (x == 2 || x == -2) && (y == 1 || y == -1) && (piece == nullptr || piece->getOwner() == 1 )) {
        
            return true;
        }
    }

    return false;
}

// g++ main.cpp source/Pawn.cpp source/Rook.cpp source/Bishop.cpp source/Queen.cpp source/Knight.cpp source/Square.cpp source/King.cpp source/Gameboard.cpp -o play -I include -L lib -l SDL2-2.0.0
