#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Square.h"
using namespace std;

class Bishop : public Piece {
	private:
			string name = "Bishop";
	public:
	Bishop(SDL_Renderer* r, int playerID);
	~Bishop();
	void setType() {type = name;}
	bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); // make sure new position is diagonal and no pieces are blocking it

};

#endif 
