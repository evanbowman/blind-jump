#pragma once
#include <random>
#include <cmath>

extern std::mt19937 globalRNG;

inline void seedRNG() {
	std::random_device rd;
	globalRNG.seed(rd() ^ time(nullptr));
}
