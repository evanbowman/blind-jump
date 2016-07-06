//
// This class exists to provide a class from which controllers may be implemented
//

#pragma once
#include <utility>

template<typename... T>
class ObjectController {
public:
	using std::tuple<T...>
}
