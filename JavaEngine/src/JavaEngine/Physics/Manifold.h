#pragma once

#include "jepch.h"
#include "RigidBody.h"
#include "JavaEngine/Core/Core.h"

namespace JPhysics
{
	template <typename Type>
	struct JE_API Manifold
	{
		RigidBody<Type>& bodyA;
		RigidBody<Type>& bodyB;
		JMaths::Vector2D<Type> normal;
		Type depth;
		JMaths::Vector2D<Type> contact1;
		JMaths::Vector2D<Type> contact2;
		Type contactCount;
	};
}
