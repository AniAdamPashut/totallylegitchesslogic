#include "moves.hpp"

bool is_legal_pawn_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	return sFile == eFile && eRank - sRank == 1;
}

bool is_legal_knight_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	if (abs(sRank - eRank) == 2) {
		return abs(sFile - eFile) == 1;
	}
	if (abs(sFile - eFile) == 2) {
		return abs(sRank - eRank) == 1;
	}
	return false;
}

bool is_legal_king_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	return abs(sRank - eRank) < 2 && abs(eFile - sFile) < 2;
}

bool is_legal_queen_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	return is_legal_bishop_move(sRank, sFile, eRank, eFile) || is_legal_rook_move(sRank, sFile, eRank, eFile);
}

bool is_legal_bishop_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	return abs((sRank - eRank) / (sFile - eFile)) == 1;
}

bool is_legal_rook_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
) {
	return sRank == eRank || sFile == eFile;
}

std::function<bool(uint8_t, uint8_t, uint8_t, uint8_t)> move_map[] = {
	is_legal_rook_move,
	is_legal_queen_move,
	is_legal_king_move,
	is_legal_knight_move,
	is_legal_bishop_move,
	is_legal_pawn_move,
};