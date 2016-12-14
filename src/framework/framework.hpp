//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include "utilities.hpp"

namespace framework {
	using Sprite = sf::Sprite;
	
	//===========================================================//
	// Framework::Object is a building block that other classes  //
	// might inherit useful features from. It is not necessary   //
	// to derive classes from this one for them to be compatible //
	// with the rest of the templates in this header.            //
	//===========================================================//
	class Object {
	protected:
		sf::Vector2f position{};
		bool killFlag = false;
		bool visible = false;
	public:
		Object(float x, float y) : position{sf::Vector2f{x, y}} {}
		inline void setPosition(sf::Vector2f _position) {
			position = _position;
		}
		inline void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}
		inline const sf::Vector2f & getPosition() const {
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
		sf::Vector2f position{};
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
		void setPosition(const sf::Vector2f & _position) {
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
	    const sf::Vector2f & getPosition() const {
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
        using containerType = std::tuple<std::vector<std::shared_ptr<Ts>>...>;
		template<std::size_t indx>
		void checkBounds() {
			static_assert(indx < std::tuple_size<containerType>::value,
						  "Error: Index out of bounds");
		}
	    containerType contents;
	public:
		template<std::size_t indx, typename ...Args>
		void add(Args && ...args) {
			checkBounds<indx>();
            using elementType = typename std::tuple_element<indx, containerType>::type::value_type::element_type; 
			std::get<indx>(contents).emplace_back(std::make_shared<elementType>(std::forward<Args>(args)...));
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
