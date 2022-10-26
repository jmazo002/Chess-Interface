#include "../header/Pawn.h"

Pawn::Pawn(SDL_Renderer* r, int playerID) { // constructor should load the appropriate texture based on team
    SDL_Surface* gImage = nullptr;
    
    if (playerID == 1) { // player 1's pieces load white assets
        gImage = SDL_LoadBMP("assets/whitePawnScaled.bmp");        
    }
    else { // player 2's pieces load black assets
        gImage = SDL_LoadBMP("assets/blackPawnScaled.bmp"); // images need to be loaded into surfaces specifically, not textures
    }
                                                        // this this surface can be converted into a texture
    this->gTexture = SDL_CreateTextureFromSurface(r, gImage);
    SDL_FreeSurface(gImage);

    this->type = "Pawn";

    this->owner = playerID;

    setName();
    
}

Pawn::~Pawn() {
    SDL_DestroyTexture(this->gTexture);

}

bool Pawn::validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block) {
   // last parameter is the piece being attacked
    
    // the position of the squares can only differ by 1 for pawns

    // black pawns should only move in the negative y direction (top->bottom)
    // white pawns should only move in the negative y direction (bottom->top)    
    bool valid = false;
    int diffX = destinationX - currentX;
    int diffY = destinationY - currentY;

    if (this->owner == 1) {
        if ((diffX == 0) && (diffY == -1) && piece == nullptr) {
            valid = true;
        }

		else if(diffX == 0 && diffY == -2 && numMoves == 0 && numMoves == 0 && piece == nullptr && block != false) {

			valid = true;  
			// can only move two steps once
		}

        else if( (diffX == 1 || diffX == -1) && diffY == -1) {
            if(piece != nullptr && piece->getOwner() == 2) { //take piece
                valid = true;
            }
        }

        else {
            //return true; // this would allow uninhibited movement
            valid = false;
        }

    }

    else if (this->owner == 2) {
        if ((diffX == 0) && (diffY == 1) && piece == nullptr) {
            valid = true;
        }

		else if(diffX == 0 && diffY == 2 && numMoves == 0 && numMoves == 0 && piece == nullptr && block != false) {
			valid = true;
		}

        else if( (diffX == 1 || diffX == -1) && diffY == 1) {
            if(piece != nullptr && piece->getOwner() == 1) { //take piece
                valid = true;
            }
        }

        else {
            //return true; // this would allow uninhibited movement
            valid = false;
        }
    }

    return valid;  
  }  

	 

