#include "QuadTree.h"


QuadTree::QuadTree() {
	boundary = Rect();
	pSize = 0;
	isDivided = false;
}

QuadTree::QuadTree(Rect& boundary) {
	this->boundary = boundary;
	pSize = 0;
	isDivided = false;
}

void QuadTree::Insert(Particle* p) {

	if (pSize < CAPACITY) {
		particles[pSize++] = p;
	} 
	else {
		if (!isDivided) 
			Divide();

		if (topLeft->boundary.DoesIntersect(p->circle))
			topLeft->Insert(p);
		else if (topRight->boundary.DoesIntersect(p->circle))
			topRight->Insert(p);
		else if (bottomLeft->boundary.DoesIntersect(p->circle))
			bottomLeft->Insert(p);
		else
			bottomRight->Insert(p);
	}
}

void QuadTree::Divide() {
	Rect tl(boundary.x - boundary.w / 2.0, boundary.y - boundary.h / 2.0, boundary.w / 2.0, boundary.h / 2.0);
	Rect tr(boundary.x + boundary.w / 2.0, boundary.y - boundary.h / 2.0, boundary.w / 2.0, boundary.h / 2.0);
	Rect bl(boundary.x - boundary.w / 2.0, boundary.y + boundary.h / 2.0, boundary.w / 2.0, boundary.h / 2.0);
	Rect br(boundary.x + boundary.w / 2.0, boundary.y + boundary.h / 2.0, boundary.w / 2.0, boundary.h / 2.0);

	topLeft = new QuadTree(tl);
	topRight = new QuadTree(tr);
	bottomLeft = new QuadTree(bl);
	bottomRight = new QuadTree(br);
	isDivided = true;

	//Distribute points amongst new quadtrees
	for (int i = 0; i < CAPACITY; i++) {
		if (topLeft->boundary.DoesIntersect(particles[i]->circle))
			topLeft->Insert(particles[i]);
		else if (topRight->boundary.DoesIntersect(particles[i]->circle))
			topRight->Insert(particles[i]);
		else if (bottomLeft->boundary.DoesIntersect(particles[i]->circle))
			bottomLeft->Insert(particles[i]);
		else
			bottomRight->Insert(particles[i]);
	}
}

std::vector<Particle*> QuadTree::GetParticlesInRegion(Rect& region) {
	std::vector<Particle*> particles;

	//Check if region intersects with us - return null if it doesn't
	if (!this->boundary.DoesIntersect(region))
		return particles;

	if (!this->isDivided) //At a leaf node, can append particles
		for (int i = 0; i < pSize; i++) {
			if(region.DoesIntersect(this->particles[i]->circle))
				particles.push_back(this->particles[i]);
		}
	else
	{
		std::vector<Particle*> tl = topLeft->GetParticlesInRegion(region);
		std::vector<Particle*> tr = topRight->GetParticlesInRegion(region);
		std::vector<Particle*> bl = bottomLeft->GetParticlesInRegion(region);
		std::vector<Particle*> br = bottomRight->GetParticlesInRegion(region);

		particles.insert(particles.end(), tl.begin(), tl.end());
		particles.insert(particles.end(), tr.begin(), tr.end());
		particles.insert(particles.end(), bl.begin(), bl.end());
		particles.insert(particles.end(), br.begin(), br.end());

	}

	return particles;
}


