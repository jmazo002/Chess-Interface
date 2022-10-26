#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
#include "Square.h"
//#include "Gameboard.h"
class Rook : public Piece { 
	
	private: 
		string name = "Rook";

	public: 
	Rook(SDL_Renderer* r, int playerID);
	~Rook();
	void setType() {type = name;}
	bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); // piece can move in any direction as long as it is not blocked by a piece 

};

#endif
