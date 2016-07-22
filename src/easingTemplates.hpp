//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

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
