#ifndef PARTICLE_H
#define PARTICLE_H

#include <random>
#include "Circle.h"

class Particle {
public:
	Circle circle;
	Color color;
	bool isIntersecting;

	Particle() {
		circle = Circle(0, 0, 0);
		color = Color(255, 255, 255);
		isIntersecting = false;
	}

	Particle(int x, int y, int radius, Color color = Color(255,255,255)) {
		this->circle = Circle(x, y, radius);
		this->color = color;
		isIntersecting = false;
	}

	Particle(Circle circle, Color color) {
		this->circle = circle;
		this->color = color;
		isIntersecting = false;
	}

	void Move() {
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> deltaX(-1, 1);
		std::uniform_int_distribution<> deltaY(-1, 1);
		circle.x += deltaX(eng);
		circle.y += deltaY(eng);
	}

	void Draw(Graphics& gfx) {
		if (isIntersecting)
			color = Color(0, 0, 255);
		else
			color = Color(255, 255, 255);

		circle.Draw(gfx, color);
	}

};

#endif