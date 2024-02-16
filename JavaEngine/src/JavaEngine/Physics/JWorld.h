#pragma once

#include "jepch.h"
#include "RigidBody.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	class JE_API JWorld
	{
	public:
		JWorld();
		~JWorld();

		void AddRigidbody(RigidBody<float>* _rigidbody);
		bool RemoveRigidbody(RigidBody<float>* _rigidbody);
		RigidBody<float>* GetRigidbody(const size_t _index) const;

		void Step(float _time);
		bool Collide(const RigidBodyf& _bodyA, const RigidBodyf& _bodyB, JMaths::Vector2Df& _normal, float& depth);
		size_t RigidbodyCount() const;

	private:
		std::vector<RigidBody<float>*> m_rigidbodyList;
		JMaths::Vector2Df m_gravity;
	};
}
