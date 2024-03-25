#pragma once

#include <cstdint>
#include "moves.hpp"

enum PieceType {
	Rook = 0,
	Queen,
	King,
	Knight,
	Bishop,
	Pawn, // able
};

enum Color {
	White,
	Black,
};

class Piece {
private:
	PieceType type;
	Color color;
public: 
	bool has_moved;

	Piece();
	Piece(PieceType t, Color c);

	~Piece();

	PieceType GetType();
	Color GetColor();
};