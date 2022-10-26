#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<string>
#include<vector>
#include<SDL2/SDL.h>
#include "Square.h"

class Gameboard {
    private:
        // objects are declared globally for ease of access in worker functions
        //SDL_Window* window;
        SDL_Renderer* renderer; // renders what's visible in the window
        SDL_Texture* gBoard; // will hold the image from a file
        SDL_Texture* player1Win;
        SDL_Texture* player2Win;
        Square* grid[8][8]; // 8x8 matrix of pointers to square objects, N(rows)xM(columns)
        vector<Piece*> deadPool;
        vector<Piece*> MovedPieces;



    public:
        Gameboard(SDL_Renderer* r); // populate the array with squares
        ~Gameboard();
        void init(); // initialize the game to a starting state, with pieces at appropriate positions
        bool drawBoard(SDL_Event* event, Square* &oldPiecePos, int &turnsTaken, const int currentPlayer, bool& gameWon); // the pointer is passed by reference so it can be updated from main(), in the function call
        void close(SDL_Window * w); // close is like destructor
        SDL_Texture* getTexture();
        void checkPawnPromotion(Square* destinationPos, const int destinationX, const int destinationY);
        bool castle(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece); 
        bool iterator(const int currentX, const int currentY, const int destinationX, const int destinationY); //checks to see if a piece's path is blocked    
        bool En_Passant(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece); 
};



#endif