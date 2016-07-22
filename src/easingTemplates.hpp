//================================================================================//
// MIT License                                                                    //
//                                                                                //
// Copyright © 2016 Evan Avery Bowman                                             //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//================================================================================//

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
