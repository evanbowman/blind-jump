#include "Effect.hpp"

Effect::Effect(float x, float y)
	: xInit(x),
	  yInit(y),
	  timer(0),
	  killFlag(false),
	  frameIndex(0)
{}

float Effect::getYpos() const {
	return yPos;
}

bool Effect::getKillFlag() const {
	return killFlag;
}
