#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Square.h"
using namespace std;

class Knight : public Piece {

	private:
	string name = "Knight";
	
	public: 
	Knight(SDL_Renderer* r, int playerID);
	~Knight();
	bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); // verify piece has moved either two spaces to the right or left and 1 space up and down or two spaces up and down and 1 space to the right or left. Ignore any pieces in the way

};

#endif 
