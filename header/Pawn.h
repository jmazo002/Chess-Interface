#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Square.h"
#include <string>
using namespace std;

class Pawn: public Piece {
	private:
	string name = "Pawn";
	
	public:
		Pawn(SDL_Renderer* r, int playerID);
		~Pawn();

		bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); // make sure pawn has moved forward or if diagonal, make sure space is occupied by enemy
		void setName() {type = name;}

};

#endif 
