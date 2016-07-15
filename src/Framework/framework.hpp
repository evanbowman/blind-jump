// Created by Evan Bowman on 7/5/16

#pragma once
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include "utilities.hpp"

using Sprite = sf::Sprite;

namespace Framework {
	//===========================================================//
	// Framework::Point simply encapsulates x,y coordinates and  //
	// provides a few overloads where meaningful.                //
	//===========================================================//
	struct Point {
		float x, y;
		inline bool operator==(const Point & other) {
			return x == other.x && y == other.y;	
		}
		inline bool operator!=(const Point & other) {
			return x != other.x || y != other.y;
		}
	};

	//===========================================================//
	// Returns the degrees in radians of the line formed by two  //
	// instances of Framework::Point                             //
	//===========================================================//
	inline float angle(const Point & p1, const Point & p2) {
		return std::atan2(p1.y - p2.y, p1.x - p2.x);
	}
	
	//===========================================================//
	// Framework::Object implements a lot of the boilerplate     //
	// code needed to put it in a group. Classes derived from    //
	// Object only need to implement their own version of the    //
	// update() function to be compatible with Framework::Group  //
	//===========================================================//
	class Object {
	protected:
		Point position{};
		bool killFlag = false;
		bool visible = false;
	public:
		Object(float x, float y) : position{Point{x, y}} {}
		inline void setPosition(Point _position) {
			position = _position;
		}
		inline void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}
		inline const Point & getPosition() const {
			return position;
		}
		inline bool getKillFlag() {
			return killFlag;
		}
		inline void setKillFlag(bool _killFlag = true) {
			killFlag = _killFlag;
		}
		inline bool isVisible() {
			return visible;
		}
		inline void setVisibility(bool _visible) {
			visible = _visible;
		}
	};

	//===========================================================//
	// A group consists of a collection of classes derived from  //
	// Framework::Object that update with the same parameters.   //
	// The class template is variadic, so you can pass any       //
	// number of arguments to its update function, as long as    //
	// they match each type in the container.                    //
	//===========================================================//
	template<typename ...Ts>
	class Group {
		template<std::size_t indx>
		void checkBounds() {
			static_assert(indx < std::tuple_size<std::tuple<std::vector<Ts>...>>::value,
						  "Error: Index out of bounds");
		}
		std::tuple<std::vector<Ts>...> contents;
	public:
		template<std::size_t indx, typename ...Args>
		void add(Args && ...args) {
			checkBounds<indx>();
			std::get<indx>(contents).emplace_back(args...);
		}
		template<std::size_t indx, typename T>
		void add(T & value) {
			checkBounds<indx>();
			std::get<indx>(contents).push_back(value);
		}
		template<std::size_t indx>
		void clear() {
			checkBounds<indx>();
			std::get<indx>(contents).clear();
		}
		void clear() {
			utilities::for_each(contents, [&](auto & vec) {
					vec.clear();
				});
		}
		template<std::size_t indx>
		auto & get() {
			checkBounds<indx>();
			return std::get<indx>(contents);
		}
		template<typename ...Args>
		void update(Args & ...args) {
			utilities::for_each(contents, [&](auto & vec) {
					for (auto it = vec.begin(); it != vec.end();) {
						if (it->getKillFlag()) {
							it = vec.erase(it);
						} else {
							it->update(args...);
							++it;
						}
					}
				});
		}
	};
}
