
#pragma once
#include <utility>
#include <vector>
#include <queue>
#include "utilities.hpp"

using Sprite = int;

namespace Framework {
	struct Point {
		float x, y;
		inline bool operator==(const Point & other) {
			return x == other.x && y == other.y;	
		}
		inline bool operator!=(const Point & other) {
			return x != other.x || y != other.y;
		}
	};
	
	template<typename T>
	class Object {
		Point position{};
		bool killFlag = false;
		bool visible = false;
	public:
		const Sprite & getSprite() {
			return static_cast<T*>(this)->getSpriteImpl();
		}
		template<typename ...Ts>
		void update(Ts & ...args) {
			static_cast<T*>(this)->updateImpl(args...);
		}
		void setPosition(Point _position) {
			position = _position;
		}
		void setPosition(float x, float y) {
			position = Point{x, y};
		}
		const Point & getPosition() const {
			return position;
		}
		bool getKillFlag() {
			return killFlag;
		}
		void setKillFlag(bool _killFlag) {
			killFlag = _killFlag;
		}
		bool isVisible() {
			return visible;
		}
		void setVisibility(bool _visible) {
			visible = _visible;
		}
	};
	
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
		auto getSprites() {
			std::vector<std::reference_wrapper<const Sprite>> sprites;
			utilities::for_each(contents, [&](auto & vec) {
					for (auto & element : vec) {
						if (element.isVisible()) {
							sprites.emplace_back(element.getSprite());
						}
					}
				});
			return sprites;
		}
	};
}
