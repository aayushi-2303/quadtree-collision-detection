#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape {
public:
	int radius;

	Circle() {
		x = y = radius = 0;
	}

	Circle(int x, int y, int r) {
		this->x = x;
		this->y = y;
		this->radius = r;
	}

	virtual void Draw(Graphics& gfx, Color color = Color(255, 255, 255)) {
		int x = radius;
		int y = 0;

		gfx.PutPixel(x + this->x, y + this->y, color);

		if (radius > 0) {
			gfx.PutPixel(x + this->x, -y + this->y, color);
			gfx.PutPixel(y + this->x, x + this->y, color);
			gfx.PutPixel(-y + this->x, x + this->y, color);
		}

		int P = 1 - radius;

		while (x > y) {
			y++;
			if (P <= 0)
				P = P + 2 * y + 1;
			else {
				x--;
				P = P + 2 * y - 2 * x + 1;
			}

			if (x < y)
				break;

			gfx.PutPixel(x + this->x, y + this->y, color);
			gfx.PutPixel(-x + this->x, y + this->y, color);
			gfx.PutPixel(x + this->x, -y + this->y, color);
			gfx.PutPixel(-x + this->x, -y + this->y, color);

			if (x != y) {
				gfx.PutPixel(y + this->x, x + this->y, color);
				gfx.PutPixel(-y + this->x, x + this->y, color);
				gfx.PutPixel(y + this->x, -x + this->y, color);
				gfx.PutPixel(-y + this->x, -x + this->y, color);
			}

		}
	}

	inline bool DoesIntersect(const Circle& other) {
		float sqDist = ((other.y - this->y) * (other.y - this->y)) + ((other.x - this->x) * (other.x - this->x));
		return (((other.radius + this->radius) * (other.radius + this->radius)) >= sqDist);
	}
};

#endif