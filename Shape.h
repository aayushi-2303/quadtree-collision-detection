#ifndef SHAPE_H
#define SHAPE_H

#include "Graphics.h"

class Shape {
public:
	int x;
	int y;
public:
	virtual void Draw(Graphics& gfx, Color color = Color(255,255,255)) = 0;
};

#endif