//
//  inputController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "inputController.hpp"
#include <cmath>

InputController::InputController() {
	x = false;
	z = false;
	c = false;
	left = false;
	right = false;
	up = false;
	down = false;
}

bool InputController::xPressed() const {
	return x;
}

bool InputController::zPressed() const {
	return z;
}

bool InputController::leftPressed() const {
	return left;
}

bool InputController::rightPressed() const {
	return right;
}

bool InputController::upPressed() const {
	return up;
}

bool InputController::downPressed() const {
	return down;
}

bool InputController::cPressed() const {
	return c;
}

void InputController::setLeft(const bool pressed) {
  left = pressed;
}

void InputController::setRight(const bool pressed) {
  right = pressed;
}

void InputController::setUp(const bool pressed) {
  up = pressed;
}

void InputController::setDown(const bool pressed) {
  down = pressed;
}

void InputController::setX(const bool pressed) {
  x = pressed;
}

void InputController::setZ(const bool pressed) {
  z = pressed;
}

void InputController::setC(const bool pressed) {
  c = pressed;
}
