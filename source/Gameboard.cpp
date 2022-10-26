#include "../header/Gameboard.h"
#include "../header/Piece.h"

#include "../header/Pawn.h"
#include "../header/King.h"
#include "../header/Queen.h"
#include "../header/Bishop.h"
#include "../header/Knight.h"
#include "../header/Rook.h"

#include <iostream>


// window dimensions are set to the dimensions of the chessboard bmp
Gameboard::Gameboard(SDL_Renderer* r) {
    // load in the gameboard texture;
    
    this->renderer = r;
    

    SDL_Surface* p1W = SDL_LoadBMP("assets/player1Win.bmp");
    this->player1Win = SDL_CreateTextureFromSurface(this->renderer, p1W);
    SDL_FreeSurface(p1W);

    SDL_Surface* p2W = SDL_LoadBMP("assets/player2Win.bmp");
    this->player2Win = SDL_CreateTextureFromSurface(this->renderer, p2W);
    SDL_FreeSurface(p2W);

    SDL_Surface* gImage = SDL_LoadBMP("assets/chessBoardGrey.bmp");   // load the chessBoard graphic into CPU memory
    this->gBoard = SDL_CreateTextureFromSurface(this->renderer, gImage); // turn chessBoard into GPU texture
    SDL_FreeSurface(gImage); // deallocate the surface after it's not needed

    // populate the gameboard with square objects
    int x = 0; int y = 0; // the x, y pixel location of each square
    for (int i = 0; i < 8; ++i) { 
        for (int j = 0; j < 8; ++j) {
            this->grid[i][j] = new Square(x, y, i, j); // making i and j data members of the square
            y += 77;
        }

        x += 77;
        y = 0; // need to reset y after each column is populated
    }
}

Gameboard::~Gameboard() { // delete the gameboard's dynamically allocated members
    // iterate through the gameboard, delete pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; i < 8; ++j) {
            if (this->grid[i][j]->getHeldPiece() != nullptr) {
                delete this->grid[i][j]->getHeldPiece();
            }
        } 
    }

    // delete pieces in the deadpool
    for (int i = 0; i < this->deadPool.size(); ++i) {
        delete this->deadPool.at(i);
    }    
    

    // deallocate gameboard object's textures
    SDL_DestroyTexture(gBoard); // deallocate the gBoard texture
    gBoard = nullptr;

    SDL_DestroyTexture(player1Win); // dealloacted P1 win splash
    player1Win = nullptr;

    SDL_DestroyTexture(player2Win); // deallocate P2 win splash
    player2Win = nullptr;

    SDL_DestroyRenderer(this->renderer); // dellocate the renderer
    this->renderer = nullptr;
}


void Gameboard::init() { // populate the board with pieces
    // for (int i = 0; i < 8; ++i) { // populate player 1's peices // this SHOULD fill every square with a piece...
    //     for (int j = 0; j < 8; ++j) {
    //         Piece* temp1 = new Piece(this->renderer, 1);
    //         this->grid[i][j]->populateSquare(temp1);
    //         temp1 = nullptr;
    //     }
    // }


// INITIALIZE ONLY PAWNS
    for (int i = 0; i < 8; ++i) { // populate player 1's peices
        for (int j = 6; j < 7; ++j) { // white pieces at bottom two rows
            Piece* temp1 = new Pawn(this->renderer, 1);
            this->grid[i][j]->populateSquare(temp1);
            temp1 = nullptr;
        }
    }

    for (int i = 0; i < 8; ++i) { // populate player 2's peices
        for (int j = 1; j < 2; ++j) { // black piexces at top 2 rows
            Piece* temp2 = new Pawn(this->renderer, 2);
            this->grid[i][j]->populateSquare(temp2);
            temp2 = nullptr;
        }
    }
    // PLAYER 1 BACKLINE
    Piece* temp3 = new Rook(this->renderer, 1);
    this->grid[0][7]->populateSquare(temp3); 
    temp3 = nullptr;

    Piece* temp4 = new Knight(this->renderer, 1);
    this->grid[1][7]->populateSquare(temp4); 
    temp4 = nullptr;

    Piece* temp5 = new Bishop(this->renderer, 1);
    this->grid[2][7]->populateSquare(temp5); 
    temp5 = nullptr;

    Piece* temp6 = new Queen(this->renderer, 1);
    this->grid[3][7]->populateSquare(temp6); 
    temp6 = nullptr;

    Piece* temp7 = new King(this->renderer, 1);
    this->grid[4][7]->populateSquare(temp7); 
    temp7 = nullptr;

    Piece* temp8 = new Bishop(this->renderer, 1);
    this->grid[5][7]->populateSquare(temp8); 
    temp8 = nullptr;

    Piece* temp9 = new Knight(this->renderer, 1);
    this->grid[6][7]->populateSquare(temp9); 
    temp9 = nullptr;

    Piece* temp10 = new Rook(this->renderer, 1);
    this->grid[7][7]->populateSquare(temp10); 
    temp10 = nullptr;


    // PLAYER 2 BACKLINE
    Piece* temp11 = new Rook(this->renderer, 2);
    this->grid[0][0]->populateSquare(temp11); 
    temp11 = nullptr;

    Piece* temp12 = new Knight(this->renderer, 2);
    this->grid[1][0]->populateSquare(temp12); 
    temp12 = nullptr;

    Piece* temp13 = new Bishop(this->renderer, 2);
    this->grid[2][0]->populateSquare(temp13); 
    temp13 = nullptr;

    Piece* temp14 = new Queen(this->renderer, 2);
    this->grid[3][0]->populateSquare(temp14); 
    temp14 = nullptr;

    Piece* temp15 = new King(this->renderer, 2);
    this->grid[4][0]->populateSquare(temp15); 
    temp15 = nullptr;

    Piece* temp16 = new Bishop(this->renderer, 2);
    this->grid[5][0]->populateSquare(temp16); 
    temp16 = nullptr;

    Piece* temp17 = new Knight(this->renderer, 2);
    this->grid[6][0]->populateSquare(temp17); 
    temp17 = nullptr;

    Piece* temp18 = new Rook(this->renderer, 2);
    this->grid[7][0]->populateSquare(temp18); 
    temp18 = nullptr;
}


SDL_Texture* Gameboard::getTexture() {
    return this->gBoard;
}



bool Gameboard::drawBoard(SDL_Event* event, Square* &toMovePos, int& turnsTaken, const int currentPlayer, bool& gameWon) {
        // turns taken is passed by reference so the accurate value is updated in main() game loop
    SDL_Point mousePos;
    //SDL_GetMouseState(&mousePos.x, &mousePos.y);
    bool quit = false;
    if (event->type == SDL_QUIT) { // check if the user has left-clicked the X to close the window
        quit = true; // handle the event, set the exit condition
        // need to poll for piece movement actions
    }


    if (gameWon == true) {
        return quit; // this should cause the game won splash screen to persist
                    // branch position should allow program to continue polling for user quit, but will ignore functionality below this line
    }
    
    
    SDL_RenderClear(this->renderer); // REMEMBER TO FLUSH OLD FRAMES FROM THE FRAME BUFFER
                                     // without this line, old frames persist and new frames are just kinda drawn on top of them
                                        // to observe this error, change the gameboard's texturepath to nonsense and compile
    
    // update the frame
    // keep drawing to the screen while the user has the program open
    

    // draw the game board texture
    SDL_RenderCopy(this->renderer, this->gBoard, NULL, NULL); // copies the image into the window render

    // copy the gameboard texture into the screen renderer, this is like drawing to the frame buffer, we load the things we want to display in a frame into the buffer before drawing the finished frame
    // after everything is loaded into the frame, we can show it to the user
    
    // draw the pieces, third argument is the rect they will be drawn to in their respective tile
    for (int i = 0; i < 8; ++i) {  // access each square in the matrix, draw the piece in it if it contains one
        for (int j = 0; j < 8; ++j) {
            if (this->grid[i][j]->getHeldPiece() != nullptr) { // if the square DOES contain a piece, draw it
                SDL_RenderCopy(this->renderer, this->grid[i][j]->getHeldPiece()->getTexture(), NULL, this->grid[i][j]->getRect());

            }
        }
    }


    if (toMovePos != nullptr) {
        // the currently selected piece should continue to glow while selected
        SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 65);
        SDL_RenderFillRect(this->renderer, toMovePos->getRect()); // selected piece glows green till moved or deselected
    }
    

    // handle polling for mouse interaction with pieces
    for (int i = 0; i < 8; ++i) {               // iterate through the board's squares, if the mouse is hovering over a rect, color it
        for (int j = 0; j < 8; ++j) {            
            if (event->type == SDL_MOUSEMOTION && currentPlayer == 1) {
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if (SDL_PointInRect(&mousePos, this->grid[i][j]->getRect())) {
                    SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 65); // squares glow blue when moused over BY PLAYER 1
                    SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect());
                }
            }

            else if (event->type == SDL_MOUSEMOTION && currentPlayer == 2) {
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if (SDL_PointInRect(&mousePos, this->grid[i][j]->getRect())) {
                    SDL_SetRenderDrawColor(this->renderer, 255, 165, 0, 65); // squares glow ORANGE when moused over BY PLAYER 2
                    SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect());
                }
            }

            if (event->type == SDL_MOUSEBUTTONDOWN) { // branch is entered whenever the user left-clicks
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                // figure out what the user was trying to interact with
                // if the user clicked on a square, and toMovePos doesn't currently point to a square
                if (SDL_PointInRect(&mousePos, this->grid[i][j]->getRect()) && (toMovePos == nullptr)) {
                    toMovePos = this->grid[i][j];
                    if (toMovePos->getHeldPiece() != nullptr && currentPlayer == toMovePos->getHeldPiece()->getOwner()) { 
                        // check if the square clicked on contained a piece and check that the piece belongs to the current player
                            // ex p1(white) should not be able to control black's pieces
                        toMovePos = this->grid[i][j]; // mark the square to move from
                        SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect()); // flash green when user clicks on a piece to move                
                    }
                    else { // if they clicked on an empty square, flash red
                        SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect());
                        toMovePos = nullptr;
                    }
                }

                else if (SDL_PointInRect(&mousePos, this->grid[i][j]->getRect()) && (toMovePos != nullptr)) { // if a toMovePos has already been marked, the user is trying to move the piece this polling cycle
                    Square* destinationPos = this->grid[i][j]; // mark the destination square;
                    int currentX = toMovePos->getGridX();
                    int currentY = toMovePos->getGridY();
                    int destinationX = destinationPos->getGridX();
                    int destinationY = destinationPos->getGridY();
               
                    if (destinationPos == toMovePos) { // if the user clicks on the currently selected piece, it is deselected
                        toMovePos = nullptr;
                    }

                    else if(castle(currentX, currentY, destinationX, destinationY, toMovePos->getHeldPiece())) {
                        toMovePos->getHeldPiece()->incrementMove(); 
                        destinationPos->populateSquare(toMovePos->getHeldPiece()); // point the piece to the destination square
                        toMovePos->populateSquare(nullptr);  // remove the piece from the old position
                        toMovePos = nullptr; // reset toMovePos for next polling cycle
                        SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect()); // flash green when the user moves the piece to a valid destination
                        ++turnsTaken; // ONLY increment turns taken when the current player performs a valid move
                    }

                    else if(En_Passant(currentX, currentY, destinationX, destinationY, toMovePos->getHeldPiece())) {
                        toMovePos->getHeldPiece()->incrementMove(); 
                        destinationPos->populateSquare(toMovePos->getHeldPiece()); // point the piece to the destination square
                        toMovePos->populateSquare(nullptr);  // remove the piece from the old position
                        toMovePos = nullptr; // reset toMovePos for next polling cycle
                        SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect()); // flash green when the user moves the piece to a valid destination
                        ++turnsTaken; // ONLY increment turns taken when the current player performs a valid move
                    }
                    
                    else if (toMovePos->getHeldPiece()->validMove(currentX, currentY, destinationX, destinationY, destinationPos->getHeldPiece(), this->iterator(currentX, currentY, destinationX, destinationY)) == true) { // if the move IS valid
                        if (destinationPos->getHeldPiece() != nullptr) { // if the current player is successfully attacking a piece, add it to the deadpool
                            this->deadPool.push_back(destinationPos->getHeldPiece());
                        }
                        MovedPieces.push_back(toMovePos->getHeldPiece());
                        toMovePos->getHeldPiece()->incrementMove(); 
                        destinationPos->populateSquare(toMovePos->getHeldPiece()); // point the piece to the destination square
                        toMovePos->populateSquare(nullptr);  // remove the piece from the old position
                        toMovePos = nullptr; // reset toMovePos for next polling cycle
                        
                        checkPawnPromotion(destinationPos, destinationX, destinationY); 

                        SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect()); // flash green when the user moves the piece to a valid destination
                        
                        
                        ++turnsTaken; // ONLY increment turns taken when the current player performs a valid move
                    }

                    else {                                                                                                                                  // if the move is invalid 
                        SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 65);
                        SDL_RenderFillRect(this->renderer, this->grid[i][j]->getRect()); // flash red if a piece is selected and the user attempts an invalid move
                    }
                }   
            }
        }   
    }

    // check for win conditions;
    for (int i = 0; i < this->deadPool.size(); ++i) { // check the deadpool if a king has been killed
        if (this->deadPool.at(i)->name() == "King") {
            if (deadPool.at(i)->getOwner() == 2) {
                SDL_RenderCopy(this->renderer, this->player1Win, NULL, NULL); // if player 2's king is killed, player 1 wins


                gameWon = true;


                //SDL_Delay(7000); // show the win screen for 7 seconds before qutiing
                
                //quit = true;

            }
            else {
                SDL_RenderCopy(this->renderer, this->player2Win, NULL, NULL);


                gameWon = true;


                //SDL_Delay(7000); // show the win screen for 7 seconds before quitting
                
                //quit = true;

            }
        }
    }


    SDL_RenderPresent(this->renderer); // draw the new frame inside the window

    return quit;
}



void Gameboard::close(SDL_Window* gWindow) { // destroys game window and quits SDL systems
    SDL_DestroyWindow(gWindow); // deallocate the game window
    gWindow = nullptr;

    SDL_Quit(); // call quit on SDL systems
}

bool Gameboard::iterator(const int currentX, const int currentY, const int destinationX, const int destinationY) {

        // rook vertical movement (I think this is for vertical. I might be wrong though)

        if(destinationX == currentX && destinationY > currentY) { // vertical movement upwards
            for(unsigned i = currentY + 1; i < destinationY; ++i) { // we do not need to check destinationY since rook's valid move function already does
                if(grid[currentX][i]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }

        else if(destinationX == currentX && destinationY < currentY) { // downwards movement
            for(unsigned i = currentY - 1; i > destinationY; --i) {
                if(grid[currentX][i]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }

        if(destinationY == currentY && destinationX > currentX) {  //horizontal 
            for(unsigned i = currentX + 1; i < destinationX; ++i) {
                if(grid[i][currentY] -> getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }

        else if(destinationY == currentY && destinationX < currentX) {
            for(unsigned i = currentX - 1; i > destinationX; --i) {
                if(grid[i][currentY] -> getHeldPiece() != nullptr) { //if there is a piece on one of those spots
                    return false;
                }
            }
        }

        // add bishop here
        if(destinationX > currentX && destinationY > currentY) { //move right+down
            unsigned x = currentX+1;
            unsigned y = currentY+1;
            
            for(x,y; x < destinationX && y < destinationY; ++x,++y) {
                if(grid[x][y]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }
        if(destinationX < currentX && destinationY < currentY) { //move left+up
            unsigned x = currentX-1;
            unsigned y = currentY-1;
            
            for(x,y; x > destinationX && y > destinationY; --x,--y) {
                if(grid[x][y]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }
        if(destinationX > currentX && destinationY < currentY) { //move right+up
            unsigned x = currentX+1;
            unsigned y = currentY-1;
            
            for(x,y; x < destinationX && y > destinationY; ++x,--y) {
                if(grid[x][y]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }
        if(destinationX < currentX && destinationY > currentY) { //move left+down
            unsigned x = currentX-1;
            unsigned y = currentY+1;
            
            for(x,y; x > destinationX && y < destinationY; --x,++y) {
                if(grid[x][y]->getHeldPiece() != nullptr) {
                    return false;
                }
            }
        }
       
        return true;
}

void Gameboard::checkPawnPromotion(Square* destinationPos, const int destinationX, const int destinationY) {
    if (destinationPos->getHeldPiece()->name() == "Pawn" && (destinationY == 0 || destinationY == 7)) //if heldPiece is a Pawn and it has reached either backrow
    {
        if (destinationPos->getHeldPiece()->getOwner() == 1) //white pawn
        {
            Piece* temp19 = new Queen(this->renderer, 1);          //replace with queen aka pawn promotion
            destinationPos->populateSquare(nullptr);
            destinationPos->populateSquare(temp19); //queen goes to destination coordinaties 
            temp19 = nullptr;
        }
        else if (destinationPos->getHeldPiece()->getOwner() == 2) //black pawn
        {
            Piece* temp20 = new Queen(this->renderer, 2);           //replace with queen aka pawn promotion
            destinationPos->populateSquare(nullptr);
            destinationPos->populateSquare(temp20); //queen goes to destination coordinaties 
            temp20 = nullptr;
        }
                            
    }
}
bool Gameboard::En_Passant(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece) {
    int x = destinationX - currentX;
    int y = destinationY - currentY;

    if(piece->name() == "Pawn") {
    
        if(piece->getOwner() == 1) {
            if( (x == 1 || x == -1) && y == -1) {
                if(this->grid[destinationX][destinationY + 1]->getHeldPiece() != nullptr && this->grid[destinationX][destinationY + 1]->getHeldPiece()->moveNum() == 1) {
                    if(this->grid[destinationX][destinationY + 1]->getHeldPiece()->name() == "Pawn" && this->grid[destinationX][destinationY + 1]->getHeldPiece()->getOwner() == 2 && MovedPieces.at(MovedPieces.size() - 1) == this->grid[destinationX][destinationY + 1]->getHeldPiece()) {
                        grid[destinationX][destinationY + 1]->populateSquare(nullptr);
                        return true;
                    }
                }
            }
        }

        else if(piece->getOwner() == 2) {
            if( (x == 1 || x == -1) && y == 1) {
                if(this->grid[destinationX][destinationY - 1]->getHeldPiece() != nullptr && this->grid[destinationX][destinationY - 1]->getHeldPiece()->moveNum() == 1) {
                    if(this->grid[destinationX][destinationY - 1]->getHeldPiece()->name() == "Pawn" && this->grid[destinationX][destinationY - 1]->getHeldPiece()->getOwner() == 1 && MovedPieces.at(MovedPieces.size() - 1) == this->grid[destinationX][destinationY - 1]->getHeldPiece()) {
                        grid[destinationX][destinationY - 1]->populateSquare(nullptr);
                        return true; 
                    }
                }
            }
        }
    }

    return false;
}

bool Gameboard::castle(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece) {

    int x = destinationX - currentX;
    int y = destinationY - currentY; 

    if(piece->name() == "King") {

        if(piece -> moveNum() != 0) {
            return false;
        }

        else{
            
            if(piece->getOwner() == 1) {
                if( x == 2 && y == 0 && iterator(currentX, currentY, 7, destinationY) ) {
                    if(grid[7][7]->getHeldPiece() != nullptr && grid[7][7]->getHeldPiece()->name() == "Rook" && grid[7][7]->getHeldPiece()->moveNum() == 0) {
                        grid[destinationX - 1][destinationY]->populateSquare(grid[7][7]->getHeldPiece());
                        grid[7][7] -> populateSquare(nullptr);
                        return true;
                    }
                }

                if( x == -2 && y == 0 && iterator(currentX, currentY, 0, destinationY) ) {
                    if(grid[0][7]->getHeldPiece() != nullptr && grid[0][7]->getHeldPiece()->name() == "Rook" && grid[0][7]->getHeldPiece()->moveNum() == 0) {
                        grid[destinationX + 1][destinationY]->populateSquare(grid[0][7]->getHeldPiece());
                        grid[0][7] -> populateSquare(nullptr);
                        return true;
                    }
                }
            }

            else if(piece->getOwner() == 2){
                 if( x == -2 && y == 0 && iterator(currentX, currentY, 0, destinationY) ) {
                    if(grid[0][0]->getHeldPiece() != nullptr && grid[0][0]->getHeldPiece()->name() == "Rook" && grid[0][0]->getHeldPiece()->moveNum() == 0) {
                        grid[destinationX + 1][destinationY]->populateSquare(grid[0][0]->getHeldPiece());
                        grid[0][0] -> populateSquare(nullptr);
                        return true;
                    }
                }

                if( x == 2 && y == 0 && iterator(currentX, currentY, 7, destinationY) ) {
                    if(grid[7][0]->getHeldPiece() != nullptr && grid[7][0]->getHeldPiece()->name() == "Rook" && grid[7][0]->getHeldPiece()->moveNum() == 0) {
                        grid[destinationX - 1][destinationY]->populateSquare(grid[7][0]->getHeldPiece());
                        grid[7][0] -> populateSquare(nullptr);
                        return true;
                    }
                }
            }
        }      

    }

    return false;
}

