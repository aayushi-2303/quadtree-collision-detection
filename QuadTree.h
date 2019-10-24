#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include "Rect.h"
#include "Particle.h"

#define CAPACITY 4

class QuadTree {
public:
	Rect boundary;
	//Point points[CAPACITY];
	Particle* particles[CAPACITY];
	QuadTree* topLeft = nullptr;
	QuadTree* topRight = nullptr;
	QuadTree* bottomLeft = nullptr;
	QuadTree* bottomRight = nullptr;
	int pSize;
	bool isDivided;

public:
	QuadTree();
	QuadTree(Rect& boundary);
	void Insert(Particle* p);
	void Divide();
	std::vector<Particle*> GetParticlesInRegion(Rect& region);
	inline bool DoesContainPoint(Particle& p) { 
		return ((p.circle.x >= boundary.x - boundary.w) && (p.circle.x < boundary.x + boundary.w) &&
		(p.circle.y >= boundary.y - boundary.h) && (p.circle.y < boundary.y + boundary.h));
	}
};

#endif