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

namespace utilities {
	template<typename TupleType, typename FunctionType>
	void for_each(TupleType&&, FunctionType,
				  std::integral_constant<size_t, std::tuple_size<typename std::remove_reference<TupleType>::type >::value>) {}

	template<std::size_t I, typename TupleType, typename FunctionType,
			 typename = typename std::enable_if<I!=std::tuple_size<typename std::remove_reference<TupleType>::type>::value>::type >
	void for_each(TupleType&& t, FunctionType f, std::integral_constant<size_t, I>) {
		f(std::get<I>(t));
		for_each(std::forward<TupleType>(t), f, std::integral_constant<size_t, I + 1>());
	}

	template<typename TupleType, typename FunctionType>
	void for_each(TupleType&& t, FunctionType f) {
		for_each(std::forward<TupleType>(t), f, std::integral_constant<size_t, 0>());
	}
	
	template<bool...> struct bool_pack;
	template<bool... bs> 
	using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
}
