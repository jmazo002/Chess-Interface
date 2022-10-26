#ifndef KING_H
#define KING_H

using namespace std;
#include "Piece.h"
#include "Square.h"
#include <string>

class King : public Piece {

	private:
	string name = "King"; // we can use this to verify a checkmate	 

	public: 
	King(SDL_Renderer* r, int playerID); //TODO
	~King();
	bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); //king can move one space in any direction
	void setType() {type = name;}
	bool Check(); //checks to see if king is in check
};

#endif
