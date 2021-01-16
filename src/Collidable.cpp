#include "Collidable.h"
#include "glm/glm.hpp"

AABB::AABB(glm::vec2 center, float width, float height)
{
	this->center = center;
	this->half_dims = glm::vec2(width / 2.f, height / 2.f);
}

CollisionType
AABB::CalculateIntersection(AABB &other)
{
	CollisionType x_coll, y_coll;
	if (MIN_DIM((*this), x) < MIN_DIM(other, x)) {
		if (MAX_DIM((*this), x) < MIN_DIM(other, x))
			return CollisionType::Outside;
		if (MAX_DIM((*this), x) < MAX_DIM(other, x))
			x_coll = CollisionType::Intersects;
		else
			x_coll = CollisionType::Contains;

	}
	else if (MIN_DIM((*this), x) >= MIN_DIM(other, x)) {
		if (MIN_DIM((*this), x) > MAX_DIM(other, x))
			return CollisionType::Outside;
		if (MAX_DIM((*this), x) <= MAX_DIM(other, x))
			x_coll = CollisionType::Inside;
		else
			x_coll = CollisionType::Intersects;
	}
	else {
		return CollisionType::Outside;
	}

	// Do the same for y
	if (MIN_DIM((*this), y) < MIN_DIM(other, y)) {
		if (MAX_DIM((*this), y) < MIN_DIM(other, y))
			return CollisionType::Outside;
		if (MAX_DIM((*this), y) < MAX_DIM(other, y))
			y_coll = CollisionType::Intersects;
		else
			y_coll = CollisionType::Contains;

	}
	else if (MIN_DIM((*this), y) >= MIN_DIM(other, y)) {
		if (MIN_DIM((*this), y) > MAX_DIM(other, y))
			return CollisionType::Outside;
		if (MAX_DIM((*this), y) <= MAX_DIM(other, y))
			y_coll = CollisionType::Inside;
		else
			y_coll = CollisionType::Intersects;
	}
	else {
		return CollisionType::Outside;
	}
	return x_coll < y_coll ? x_coll : y_coll;
}