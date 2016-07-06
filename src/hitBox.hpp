#pragma once

template <uint8_t w, uint8_t h, uint8_t xOff, uint8_t yOff>
class HitBox {
	float * pXPos, * pYPos;
	
public:
	explicit HitBox(float * _pXPos, float * _pYPos) :
		pXPos{_pXPos},
		pYPos{_pYPos}
	{}
	
	constexpr uint8_t getWidth() const {
		return w;
	}
	
	constexpr uint8_t getHeight() const {
		return h;
	}
	
	float getXPos() const {
		return *pXPos + xOff;
	}
	
	float getYPos() const {
		return *pYPos + yOff;
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
