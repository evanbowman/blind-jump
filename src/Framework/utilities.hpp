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
