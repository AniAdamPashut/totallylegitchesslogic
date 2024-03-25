#include "piece.hpp"

Piece::Piece() {

}

Piece::~Piece() {}

Piece::Piece(PieceType t, Color c) {
	this->type = t;
	this->color = c;
	this->has_moved = false;
}

PieceType Piece::GetType() {
	return this->type;
} 

Color  Piece::GetColor() {
	return this->color;
}

