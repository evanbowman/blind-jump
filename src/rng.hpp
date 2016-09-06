//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <random>
#include <cmath>

namespace rng {
	extern std::mt19937 RNG;

	template <size_t upper, int lower = 0>
	int random() {
		return std::abs(static_cast<int>(RNG())) % upper + lower;
	}
	
	inline int random(size_t upper, int lower = 0) {
		return std::abs(static_cast<int>(RNG())) % upper + lower;
	}

	inline void seed() {
		std::random_device rd;
		RNG.seed(rd() ^ time(nullptr));
	}
}
