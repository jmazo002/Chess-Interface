#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Square.h"

#include "Rook.h"
#include "Bishop.h"
using namespace std;

class Queen : public Piece {
	private:

	string name = "Queen";
	void setType() {type = name;}
	
	public:
	Queen(SDL_Renderer* r, int playerID);
	~Queen();
	bool validMove(const int currentX, const int currentY, const int destinationX, const int destinationY, Piece* piece, bool block); // queen can move anywhere as long as it is not blocked 

};

#endif
