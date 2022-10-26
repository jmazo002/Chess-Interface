#include "../header/Square.h"


Square::Square(int x, int y, int gridX, int gridY) {

    this->rect = new SDL_Rect; // rect is a struct, not a C++ class!

    // the x,y pixel location for the rect's origin
    this->rect->x = x;
    this->rect->y = y;

    // the box will have these dimensions
    this->rect->w = 77;
    this->rect->h = 77;

    this->gridX = gridX;
    this->gridY = gridY;

    this->heldPiece = nullptr; // initalizes square to empty
}

SDL_Rect* Square::getRect() {
    return this->rect;
}

void Square::populateSquare(Piece* piece) {
    this->heldPiece = piece;
   // piece->setSquare(this); // assign square to piece's square pointer
}

Piece* Square::getHeldPiece() {
    return this->heldPiece;
}

int Square::getGridX() {
    return this->gridX;
}

int Square::getGridY() {
    return this->gridY;
}