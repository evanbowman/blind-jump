#pragma once
#include <cmath>

namespace Easing {
	template<std::size_t dim, typename T>
	float easeIn(T current, T duration) {
		if (current >= duration) {
			return 1.f;
		}
		return static_cast<float>(std::pow(current, dim)) / static_cast<float>(std::pow(duration, dim));
	}
	
	template<std::size_t dim, typename T>
	float easeOut(T current, T duration) {
		return 1.f - easeIn<dim>(current, duration);
	}
}
