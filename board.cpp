#include "board.hpp"
#include "moves.hpp"

#pragma warning(disable:6385)


/*
7	R N B Q K B N R
6	P P P P P P P P
5	- - - - - - - -
4	- - - - - - - -
3	- - - - - - - -
2	- - - - - - - -
1	p p p p p p p p
0	r n b q k b n r
    
	a b c d e f g h
*/

#define HEIGHT 8
#define WIDTH 8

Board::Board() {
	PieceType order[WIDTH] = {
		Rook,
		Knight,
		Bishop,
		Queen,
		King,
		Bishop,
		Knight,
		Rook
	};
	//[](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return true; };
	traceback[Rook] = [this](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return this->rook_traceback(sRank, sFile, eRank, eFile); };
	traceback[Bishop] = [this](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return this->bishop_traceback(sRank, sFile, eRank, eFile); };
	traceback[Queen] = [this](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return this->queen_traceback(sRank, sFile, eRank, eFile); };
	traceback[King] = [](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return true; };
	traceback[Pawn] = [](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return true; };
	traceback[Knight] = [](uint8_t sRank, uint8_t sFile, uint8_t eRank, uint8_t eFile) { return true; };

	for (int i = 0; i < WIDTH; i++) {
		// Second rank
		state[1][i] = std::optional<Piece>(Piece(Pawn, White));
		// Seventh Rank
		state[6][i] = std::optional<Piece>(Piece(Pawn, Black));
		// First Rank
		state[0][i] = std::optional<Piece>(Piece(order[i], White));
		// Eighth Rank
		state[7][i] = std::optional<Piece>(Piece(order[i], Black));
		state[2][i] = std::nullopt;
		state[3][i] = std::nullopt;
		state[4][i] = std::nullopt;
		state[5][i] = std::nullopt;
	}
}

Board::~Board() {}
// .map(it == std::nullopt).all();
bool Board::bishop_traceback(
	uint8_t start_rank,
	uint8_t start_file,
	uint8_t end_rank,
	uint8_t end_file
) {
	int x_cumm = end_rank - start_rank;
	int y_cumm = end_file - start_file;
	for (int i = start_file, j = start_rank; i != end_file && j != end_rank; i += y_cumm, j += x_cumm) {
		if (state[j][i].has_value()) return false;
	}
	return true;
}

bool Board::rook_traceback(
	uint8_t start_rank,
	uint8_t start_file,
	uint8_t end_rank,
	uint8_t end_file
) {
	if (start_rank == end_rank) {
		for (int i = start_file; i < end_file; i++) {
			if (state[start_rank][i].has_value()) return false;
		}

		return true;
	}
	if (start_file == end_file) {
		for (int i = start_rank; i < end_rank; i++) {
			if (state[i][start_file].has_value()) return false;
		}

		return true;
	}
	return false;
}

bool Board::queen_traceback(
	uint8_t start_rank,
	uint8_t start_file,
	uint8_t end_rank,
	uint8_t end_file
) {
	if (is_legal_bishop_move(start_rank, start_file, end_rank, end_file)) {
		return bishop_traceback(start_rank, start_file, end_rank, end_file);
	}
	return rook_traceback(start_rank, start_file, end_rank, end_file);
}

bool Board::Move(
	uint8_t start_rank, uint8_t start_file,
	uint8_t end_rank, uint8_t end_file
) {
	// Validate rank and file positioning
	if ((start_rank > 7 || start_rank < 0) && (start_file < 0 || start_file > 7)) {
		return false;
	}

	if ((end_rank > 7 || end_rank < 0) && (end_file < 0 || end_file > 7)) {
		return false;
	}

	std::optional<Piece>& pos = state[start_rank][start_file];

	if (!pos.has_value()) {
		return false;
	}

	Piece curr = pos.value();

	
	std::optional<Piece>& end_pos = state[end_rank][end_file];

	if (end_pos.has_value() && end_pos.value().GetColor() == curr.GetColor()) {
		return false;
	}

	if (curr.GetType() == Pawn) {
		// 2-advance
		if ((start_file == end_file) && (end_rank - start_rank == 2) && !curr.has_moved) {
			state[end_rank][end_file] = state[start_rank][start_file];
			state[end_rank][end_file].value().has_moved = true;
			state[start_rank][start_file] = std::nullopt;
			return true;
		}

		if ((abs(start_file - end_file) == 1) && (end_rank - start_rank == 1) && end_pos.has_value()) {
			state[end_rank][end_file] = state[start_rank][start_file];
			state[end_rank][end_file].value().has_moved = true;
			state[start_rank][start_file] = std::nullopt;
			return true;
		}

		if (end_pos.has_value()) {
			// that means that a pawn tries to advance on enemy piece (he can't)
			return false; 
		}
	}


	bool is_valid = move_map[curr.GetType()](start_rank, start_file, end_rank, end_file);
	if (!is_valid) {
		return false;
	}

	if (!traceback[curr.GetType()](start_rank, start_file, end_rank, end_file)) {
		return false;
	}
	
	state[end_rank][end_file] = state[start_rank][start_file];
	state[end_rank][end_file].value().has_moved = true;
	state[start_rank][start_file] = std::nullopt;
	return true;
}