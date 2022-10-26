#include "../header/Rook.h"


Rook::Rook(SDL_Renderer* r, int playerID) { // constructor should load the appropriate texture based on team
    SDL_Surface* gImage = nullptr;
    
    if (playerID == 1) { // player 1's pieces load white assets
        gImage = SDL_LoadBMP("assets/whiteRookScaled.bmp");        
    }
    else { // player 2's pieces load black assets
        gImage = SDL_LoadBMP("assets/blackRookScaled.bmp"); // images need to be loaded into surfaces specifically, not textures
    }
                                                        // this this surface can be converted into a texture
    this->gTexture = SDL_CreateTextureFromSurface(r, gImage);
    SDL_FreeSurface(gImage);

    this->type = "Rook";

    this->owner = playerID;
    setType();
}

Rook::~Rook() {
    SDL_DestroyTexture(this->gTexture);
}

bool Rook::validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) // piece can move in any direction as long as it is not blocked by a piece
{
    // last parameter is the piece being attacked
    // rooks can move horizontally and vertically 
    //&& block != false checks if the piece is blocked
    if (this->owner == 1) 
    {
        if (destinationX == currentX && piece == nullptr && block != false)  // valid if in the same column
        {
            return true;
        }
        else if (destinationY == currentY && piece == nullptr && block != false) // valid if in the same row
        {
            return true;
        }
        else if ((destinationX == currentX || destinationY == currentY) && piece != nullptr && piece->getOwner() == 2 && block != false) //valid if in the same row or column and it is opponent piece
        {
            return true;
        }
    }
    else if (this->owner == 2) 
    {
        if (destinationX == currentX && piece == nullptr && block != false) // valid if in the same column
        {
            return true;

        }
        else if (destinationY == currentY && piece == nullptr && block != false) // valid if in the same row
        {
            return true;
        }
        else if ((destinationX == currentX || destinationY == currentY) && piece != nullptr &&  piece->getOwner() == 1 && block != false) //valid if in the same row or column and it is opponent piece
        {
            return true;
        }

    }

    return false;
    
}