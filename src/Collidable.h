#pragma once
#include "glm/vec2.hpp"

#define MIN_DIM(aabb, dim) aabb.center.##dim - aabb.half_dims.##dim
#define MAX_DIM(aabb, dim) aabb.center.##dim + aabb.half_dims.##dim

enum CollisionType {
	Outside,
	Intersects,
	Inside,
	Contains,
};

class AABB {
public:
	AABB(glm::vec2 center, float width, float height);
	AABB() = default;

	// Returns Intersection enum in relation to 'other'
	CollisionType CalculateIntersection(AABB &other);

	glm::vec2 center;
	glm::vec2 half_dims;
};

class Collidable {

public:
	Collidable(AABB &bounds) { bbox = bounds; };
	Collidable() = default;
	virtual CollisionType Collide(Collidable &other) { return this->bbox.CalculateIntersection(other.bbox); };
	AABB bbox;
};