//#include "King.h"
#include "../header/King.h"

King::King(SDL_Renderer* r, int playerID) { // constructor should load the appropriate texture based on team
    SDL_Surface* gImage = nullptr;
    
    if (playerID == 1) { // player 1's pieces load white assets
        gImage = SDL_LoadBMP("assets/whiteKingScaled.bmp");        
    }
    else { // player 2's pieces load black assets
        gImage = SDL_LoadBMP("assets/blackKingScaled.bmp"); // images need to be loaded into surfaces specifically, not textures
    }
                                                        // this this surface can be converted into a texture
    this->gTexture = SDL_CreateTextureFromSurface(r, gImage);
    SDL_FreeSurface(gImage);

    this->type = "King";

    this->owner = playerID;
    setType();
}

King::~King() {
    SDL_DestroyTexture(this->gTexture);
}

bool King::validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) {
    
    bool valid = false;
    int x = destinationX - currentX;
    int y = destinationY - currentY;

    if(this->owner == 1) {
        if((x == 1 || x == -1) && y == 0) { // horizontal movement
            if(piece == nullptr || piece->getOwner() == 2) { // new position has no piece or position has an enemy piece
                valid = true;
            }
        }

        else if(x == 0 && ( y == 1 || y == -1)) { //vertical movement
            if(piece == nullptr || piece->getOwner() == 2) {
                valid = true;
            }
        }
        
        else if( (x ==-1 || x == 1) && (y == 1 || y == -1)  ) {
            if(piece == nullptr || piece->getOwner() == 2) {
                valid = true;
            }
        }

        else {
            valid = false; }
    }

    else if(this->owner == 2) {
         if((x == 1 || x == -1) && y == 0) { // horizontal movement
            if(piece == nullptr || piece->getOwner() == 1) { // new position has no piece or position has an enemy piece
                valid = true;
            }
        }

        else if(x == 0 && ( y == 1 || y == -1)) { //vertical movement
            if(piece == nullptr || piece->getOwner() == 1) {
                valid = true;
            }
        }

         else if( (x ==-1 || x == 1) && (y == 1 || y == -1)  ) {
            if(piece == nullptr || piece->getOwner() == 1) {
                valid = true;
            }
        }

        else {
            valid = false; }
    }

    return valid;

}

bool King::Check() {
    // TODO
    return false;
}
