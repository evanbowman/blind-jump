#pragma once

template <uint8_t w, uint8_t h, uint8_t xOff, uint8_t yOff>
class HitBox {
	static_assert(w > 0 && h > 0, "Zero is not a valid Hitbox side length parameter");
	float xPos, yPos;
	
public:
	HitBox() : xPos{0.f}, yPos{0.f} {}

	void setPosition(float _xPos, float _yPos) {
		xPos = _xPos;
		yPos = _yPos;
	}
	
	constexpr uint8_t getWidth() const {
		return w;
	}
	
	constexpr uint8_t getHeight() const {
		return h;
	}
	
	float getXPos() const {
		return xPos + xOff;
	}
	
	float getYPos() const {
		return yPos + yOff;
	}
};

template <typename T1, typename T2>
bool overlapping(const T1 & hB1, const T2 & hB2) {
	if (hB1.getXPos() < (hB2.getXPos() + hB2.getWidth()) &&
		(hB1.getXPos() + hB1.getWidth()) > hB2.getXPos() &&
		hB1.getYPos() < (hB2.getYPos() + hB2.getHeight()) &&
		(hB1.getYPos() + hB1.getHeight()) > hB2.getYPos()) {
		return true;
	}
	return false;
}
