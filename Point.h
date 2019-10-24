#ifndef POINT_H
#define POINT_H

#include "Shape.h"

class Point : public Shape {
public:

	Point() {
		x = y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	virtual void Draw(Graphics& gfx, Color color = Color(255,255,255)) {
		gfx.PutPixel(x, y, color);
	}
};

#endif