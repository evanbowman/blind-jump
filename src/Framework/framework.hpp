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
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include "utilities.hpp"

using Sprite = sf::Sprite;

namespace Framework {
	//===========================================================//
	// Framework::Point simply encapsulates x,y coordinates      //
	//===========================================================//
	struct Point {
		float x, y;
	};
	
	//===========================================================//
	// Returns the degrees in radians of the line formed by two  //
	// instances of Framework::Point                             //
	//===========================================================//
	inline float angle(const Point & p1, const Point & p2) {
		return std::atan2(p1.y - p2.y, p1.x - p2.x);
	}
	
	//===========================================================//
	// Framework::Object is a building block that other classes  //
	// might inherit useful features from. It is not necessary   //
	// to derive classes from this one for them to be compatible //
	// with the rest of the templates in this header.            //
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
	// A simple collision rectangle, with member function for    //
	// checking overlap with other collision rectangles. w and h //
	// represent width and height, xOff and yOff denote the      //
	// offset between the box's upper left corner and its        //
	// position.                                                 //
	//===========================================================//
	template<int16_t w, int16_t h, int16_t xOff = 0, int16_t yOff = 0>
	class HitBox {
		static_assert(w > 0 && h > 0, "Zero and negative values are not valid Hitbox side length parameters");
		Point position{};
        #ifdef DEBUG
		sf::RectangleShape rect; // If in debug mode provide visual representations for hitBoxes
        #endif
    public:
		HitBox() {
            #ifdef DEBUG
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Red);
			rect.setOutlineThickness(1);
			rect.setSize(sf::Vector2f(w, h));
            #endif
		}
		void setPosition(const Point & _position) {
			position.x = _position.x;
			position.y = _position.y;
            #ifdef DEBUG
			rect.setPosition(_position.x + xOff, position.y + yOff);
            #endif
		}
		#ifdef DEBUG
		const sf::RectangleShape & getDrawableRect() const {
			return rect;
		}
		#endif
		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
			#ifdef DEBUG
			rect.setPosition(x + xOff, y + yOff);
			#endif
		}
	    const Point & getPosition() const {
			return position;
		}
	    constexpr uint16_t getWidth() const {
			return w;
		}
	    constexpr uint16_t getHeight() const {
			return h;
		}
	    float getXPos() const {
			return position.x + xOff;
		}
	    float getYPos() const {
			return position.y + yOff;
		}
	    template<typename T>
		bool overlapping(const T & other) const {
			if (this->getXPos() < (other.getXPos() + other.getWidth()) &&
				(this->getXPos() + w) > other.getXPos() &&
				this->getYPos() < (other.getYPos() + other.getHeight()) &&
				(this->getYPos() + h) > other.getYPos()) {
				return true;
			}
			return false;
		}
	};
	
	//===========================================================//
	// Framework::Group is a structure that can hold any number  //
	// of classes of different type. It also provides an         //
	// interface for applying function pointers or lambdas to    //
	// the contained data.                                       //
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
			std::get<indx>(contents).emplace_back(std::forward<Args>(args)...);
		}
		template<std::size_t indx, typename T>
		void add(T & value) {
			checkBounds<indx>();
			std::get<indx>(contents).push_back(value);
		}
		template<std::size_t indx, typename T>
		void add(T && value) {
			checkBounds<indx>();
			std::get<indx>(contents).push_back(std::forward<T>(value));
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
		template<std::size_t indx>
		const auto & get() const {
			checkBounds<indx>();
			return std::get<indx>(contents);
		}
		template<typename F>
		void apply(const F & hook) {
			utilities::for_each(contents, hook);
		}
		template<std::size_t indx, typename F>
		void apply(const F & hook) {
			checkBounds<indx>();
			hook(std::get<indx>(contents));
		}
	};
}
