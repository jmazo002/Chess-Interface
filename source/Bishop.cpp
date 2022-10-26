#include "../header/Bishop.h"

Bishop::Bishop(SDL_Renderer* r, int playerID) { // constructor should load the appropriate texture based on team
    SDL_Surface* gImage = nullptr;
    
    if (playerID == 1) { // player 1's pieces load white assets
        gImage = SDL_LoadBMP("assets/whiteBishopScaled.bmp");        
    }
    else { // player 2's pieces load black assets
        gImage = SDL_LoadBMP("assets/blackBishopScaled.bmp"); // images need to be loaded into surfaces specifically, not textures
    }
                                                        // this this surface can be converted into a texture
    this->gTexture = SDL_CreateTextureFromSurface(r, gImage);
    SDL_FreeSurface(gImage);

    this->type = "Bishop";

    this->owner = playerID;
}

Bishop::~Bishop() {
    SDL_DestroyTexture(this->gTexture);
}

bool Bishop::validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) {// piece can move in any direction as long as it is not blocked by a piece
    int x = abs(destinationX - currentX);
    int y = abs(destinationY - currentY);
    
    if (this->owner == 1) {
        if(destinationX >= 0 && destinationY >= 0 && destinationX < 8 && destinationY < 8 && piece == nullptr && block != false) {
            if(x == y && x > 0) {
                return true;
            }
        }
        else if((destinationX >= 0 && destinationY >= 0 && destinationX < 8 && destinationY < 8) && piece != nullptr && piece->getOwner() == 2 && block != false) {
            if(x == y && x > 0) {
                return true;
            }
        }
    }
    if (this->owner == 2) {
        if(destinationX >= 0 && destinationY >= 0 && destinationX < 8 && destinationY < 8 && piece == nullptr && block != false) {
            if(x == y && x > 0) {
                return true;
            }
        }
        else if((destinationX >= 0 && destinationY >= 0 && destinationX < 8 && destinationY < 8) && piece != nullptr && piece->getOwner() == 1 && block != false) {
            if(x == y && x > 0) {
                return true;
            }
        }
    }
    return false;
}