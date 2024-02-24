#pragma once

#include "jepch.h"
#include "Manifold.h"
#include "RigidBody.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	struct ContactPair
	{
		int item1;
		int item2;
	};

	class JE_API JWorld
	{
	public:
		JWorld();
		~JWorld();

		void AddRigidbody(RigidBody<float>* _rigidbody);
		bool RemoveRigidbody(RigidBody<float>* _rigidbody);
		RigidBody<float>* GetRigidbody(const size_t _index) const;

		void Step(float _time, int _iterations);
		void StepBodies(float _time, float _iterations);
		size_t RigidbodyCount() const;

		static constexpr int MinIteration = 1;
		static constexpr int MaxIteration = 128;

		std::vector<JMaths::Vector2Df> m_contactPointsList;
	protected:
		void BroadPhase();
		void NarrowPhase();
		void ResolveCollision(Manifold<float>& _contact);
		void SeparateBodies(RigidBodyf& _bodyA, RigidBodyf& _bodyB, const JMaths::Vector2Df& _normal, float& _depth);

	private:
		std::vector<RigidBody<float>*> m_rigidbodyList;
		JMaths::Vector2Df m_gravity;
		//std::vector<Manifold<float>*> m_contactList;
		std::vector<ContactPair> m_contactPair;
	};
}
