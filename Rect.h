#ifndef RECT_H
#define RECT_H

#include "Shape.h"
#include "Point.h"
#include "Circle.h"

class Rect: public Shape {
public:
	float w;
	float h;

public:
	Rect() {
		x = y = w = h = 0;
	}

	Rect(int x, int y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	virtual void Draw(Graphics& gfx, Color color = Color(255, 255, 255)) {
		//Top
		DrawLine(Point(x - w, y - h), Point(x + w, y - h), gfx, color);
		//Bottom
		DrawLine(Point(x - w, y + h), Point(x + w, y + h), gfx, color);
		//Left
		DrawLine(Point(x - w, y - h), Point(x - w, y + h), gfx, color);
		//Right
		DrawLine(Point(x + w, y - h), Point(x + w, y + h), gfx, color);
	}

	inline bool DoesIntersect(Rect& other) {
		if ((other.x - other.w > this->x + this->w) || (other.x + other.w < this->x - this->w) ||
			(other.y - other.h > this->y + this->h) || (other.y + other.h < this->y - this->h))
			return false;
		return true;
	}

	inline bool DoesIntersect(Point& p) {
		return ((p.x >= x - w) & (p.x < x + w) &&
			(p.y >= y - h) && (p.y < y + h));
	}

	//Improve to check for whole circle
	inline bool DoesIntersect(Circle& c) {
		bool b = ((c.x >= x - w) & (c.x < x + w) &&
			(c.y >= y - h) && (c.y < y + h));
		return ((c.x >= x - w) & (c.x < x + w) &&
			(c.y >= y - h) && (c.y < y + h));
	}

	void DrawLine(Point& start, Point& fin, Graphics& gfx, Color color = Color(255,255,255)) {
		bool steep = (fabs(fin.y - start.y) > fabs(fin.x - start.x));
		if (steep) {
			std::swap(start.x, start.y);
			std::swap(fin.x, fin.y);
		}
		if (start.x > fin.x) {
			std::swap(start.x, fin.x);
			std::swap(start.y, fin.y);
		}

		const float dx = fin.x - start.x;
		const float dy = fabs(fin.y - start.y);

		float error = dx / 2.0f;
		const int ystep = (start.y < fin.y) ? 1 : -1;
		int y = (int)start.y;

		const int maxX = (int)fin.x;

		for (int x = (int)start.x; x < maxX; x++) {
			if (steep)
				gfx.PutPixel(y, x, color);
			else
				gfx.PutPixel(x, y, color);

			error -= dy;
			if (error < 0) {
				y += ystep;
				error += dx;
			}
		}
	}
};


#endif