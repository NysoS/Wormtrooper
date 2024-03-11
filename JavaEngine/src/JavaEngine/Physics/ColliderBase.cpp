#include "ColliderBase.h"
#include "JavaEngine/Physics/RigidBody.h"

namespace JavaEngine
{
	ColliderBase::ColliderBase(const JMaths::Vector2Df& pos, float angle)
		: position(pos), angle(angle)
	{
	}

	ColliderBase::~ColliderBase()
	{
	}
}
