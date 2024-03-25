#pragma once

#include <array>
#include <optional>
#include <functional>
#include <unordered_map>

#include "piece.hpp"

class Board {
private:
	std::optional<Piece> state[8][8];
	bool rook_traceback (
		uint8_t start_rank,
		uint8_t start_file,
		uint8_t end_rank,
		uint8_t end_file
	);
	bool bishop_traceback (
		uint8_t start_rank,
		uint8_t start_file,
		uint8_t end_rank,
		uint8_t end_file
	);
	bool queen_traceback (
		uint8_t start_rank,
		uint8_t start_file,
		uint8_t end_rank,
		uint8_t end_file
	);

	std::array<std::function<bool(uint8_t, uint8_t, uint8_t, uint8_t)>, 6> traceback;
public:
	Board();
	bool Move(
		uint8_t start_rank,
		uint8_t start_file, 
		uint8_t end_rank, 
		uint8_t end_file
	);
	
	~Board();
};