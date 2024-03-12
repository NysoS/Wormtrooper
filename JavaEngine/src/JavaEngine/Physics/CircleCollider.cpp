#include "CircleCollider.h"

namespace JavaEngine
{
	CircleCollider::CircleCollider(float radius, const JMaths::Vector2Df& pos, float angle)
		: ColliderBase(pos, angle), radius(radius)
	{
	}

	CircleCollider::~CircleCollider()
	{
	}
}
