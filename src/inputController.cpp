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

void InputController::update() {
  
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

void InputController::setLeft(bool pressed) {
  left = pressed;
}

void InputController::setRight(bool pressed) {
  right = pressed;
}

void InputController::setUp(bool pressed) {
  up = pressed;
}

void InputController::setDown(bool pressed) {
  down = pressed;
}

void InputController::setX(bool pressed) {
  x = pressed;
}

void InputController::setZ(bool pressed) {
  z = pressed;
}

void InputController::setC(bool pressed) {
  c = pressed;
}
