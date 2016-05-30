//
//  GradientCircle.cpp
//  gradientCircleTest
//
//  Created by Evan Bowman on 5/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "GradientCircle.hpp"
#include <cmath>

#define PI 3.141592654f
#define DEFAULT_POINT_COUNT 40
#define DEFAULT_RADIUS 80.f
#define DEFAULT_COORDINATE_X 200.f
#define DEFAULT_COORDINATE_Y 200.f

GradientCircle::GradientCircle() {
	// The +2 accounts for the default center point, as well as an additional point to complete the circle
	vertices.resize(DEFAULT_POINT_COUNT + 2);
	
	radius = DEFAULT_RADIUS;
	xPos = DEFAULT_COORDINATE_X;
	yPos = DEFAULT_COORDINATE_Y;
	
	vertices.setPrimitiveType(sf::TrianglesFan);
	setOuterColor(sf::Color::White);
	setCenterColor(sf::Color::Transparent);
	setPointCount(DEFAULT_POINT_COUNT);
}

void GradientCircle::setPosition(float xPos, float yPos) {
	float angle;
	
	vertices[0].position = sf::Vector2f(xPos, yPos);
	
	long int pointCount = vertices.getVertexCount();
	for (int i = 1; i < pointCount; i++) {
		angle = i * 2 * PI / (pointCount - 2) - PI / 2;
		vertices[i].position = sf::Vector2f(xPos + radius * std::cosf(angle), yPos + radius * std::sinf(angle));
	}
}

void GradientCircle::setOuterColor(const sf::Color color) {
	long int pointCount = vertices.getVertexCount();
	for (int i = 1; i < pointCount; i++) {
		vertices[i].color = color;
	}
}

float GradientCircle::getRadius() const {
	return radius;
}

sf::Color GradientCircle::getOuterColor() const {
	return vertices[1].color;
}

sf::Color GradientCircle::getCenterColor() const {
	return vertices[0].color;
}

void GradientCircle::setCenterColor(const sf::Color color) {
	vertices[0].color = color;
}

void GradientCircle::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
	target.draw(vertices, states);
}

void GradientCircle::setPointCount(int pointCount) {
	vertices.resize(static_cast<size_t>(pointCount + 2));
	float angle;
	vertices[0].position = sf::Vector2f(xPos, yPos);
	for (int i = 1; i < pointCount + 2; i++) {
		angle = i * 2 * PI / pointCount - PI / 2;
		vertices[i].position = sf::Vector2f(xPos + radius * std::cosf(angle), yPos + radius * std::sinf(angle));
	}
}

void GradientCircle::setRadius(float radius) {
	this->radius = radius;
	float angle;
	long int pointCount = vertices.getVertexCount();
	for (int i = 1; i < pointCount; i++) {
		angle = i * 2 * PI / (pointCount - 2) - PI / 2;
		vertices[i].position = sf::Vector2f(xPos + radius * std::cosf(angle), yPos + radius * std::sinf(angle));
	}
}
