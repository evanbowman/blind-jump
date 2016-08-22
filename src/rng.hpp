//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <random>
#include <cmath>

namespace global {
	extern std::mt19937 RNG;
}

inline void seedRNG() {
	std::random_device rd;
	global::RNG.seed(rd() ^ time(nullptr));
}
