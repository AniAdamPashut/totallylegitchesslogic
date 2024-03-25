#pragma once
	
#include <functional>

bool is_legal_pawn_move(
	uint8_t sRank, uint8_t sFile, 
	uint8_t eRank, uint8_t eFile
);

bool is_legal_knight_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
);

bool is_legal_king_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
);

bool is_legal_queen_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
);

bool is_legal_bishop_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
);

bool is_legal_rook_move(
	uint8_t sRank, uint8_t sFile,
	uint8_t eRank, uint8_t eFile
);

std::function<bool(uint8_t, uint8_t, uint8_t, uint8_t)> move_map[] = {
	is_legal_rook_move,
	is_legal_queen_move,
	is_legal_king_move,
	is_legal_knight_move,
	is_legal_bishop_move,
	is_legal_pawn_move,
};