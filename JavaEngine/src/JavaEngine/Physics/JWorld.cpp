#include "JavaEngine/Physics/JWorld.h"

#include "Collisions.h"

namespace JPhysics
{
	JWorld::JWorld()
		: m_gravity(JMaths::Vector2Df(0, 9.81f))
	{
	}

	JWorld::~JWorld()
	{
	}

	void JWorld::AddRigidbody(RigidBody<float>* _rigidbody)
	{
		/*if(std::find(m_rigidbodyList.begin(), m_rigidbodyList.end(), _rigidbody) != m_rigidbodyList.end())
		{
			return;
		}*/

		m_rigidbodyList.push_back(_rigidbody);
	}

	bool JWorld::RemoveRigidbody(RigidBody<float>* _rigidbody)
	{
		auto it = std::find(m_rigidbodyList.begin(), m_rigidbodyList.end(), _rigidbody);

		if(it == m_rigidbodyList.end())
		{
			return false;
		}

		m_rigidbodyList.erase(it);
		return true;
	}

	RigidBody<float>* JWorld::GetRigidbody(const size_t _index) const
	{
		if(_index < 0 || _index >= m_rigidbodyList.size())
		{
			return nullptr;
		}

		return m_rigidbodyList.at(_index);
	}

	void JWorld::Step(float _time, int _iterations)
	{
		int iterations = JMaths::JMath<int>::Clamp(_iterations, MinIteration, MaxIteration);

		m_contactPointsList.clear();

		for (int it = 0; it < iterations; ++it)
		{
			//m_contactList.clear();
			m_contactPair.clear();

			//Movement step
			StepBodies(_time, static_cast<float>(iterations));

			//Collision step
			BroadPhase();
			NarrowPhase();
			
		}
	}

	void JWorld::StepBodies(float _time, float _iterations)
	{
		for (int i = 0; i < m_rigidbodyList.size(); ++i)
		{
			m_rigidbodyList[i]->Step(_time, m_gravity, _iterations);
		}
	}

	size_t JWorld::RigidbodyCount() const
	{
		return m_rigidbodyList.size();
	}

	void JWorld::BroadPhase()
	{
		for (int i = 0; i < m_rigidbodyList.size() - 1; ++i)
		{
			RigidBodyf* bodyA = m_rigidbodyList[i];
			AABB<float> aabb_bodyA = bodyA->GetAABB();

			for (int j = 1; j < m_rigidbodyList.size(); ++j)
			{
				RigidBodyf* bodyB = m_rigidbodyList[j];
				AABB<float> aabb_bodyB = bodyB->GetAABB();

				if (bodyA->isStatic && bodyB->isStatic)
				{
					continue;
				}

				if (bodyA == bodyB)
				{
					continue;
				}

				if (!Collisions<float>::IntersectAABB(aabb_bodyA, aabb_bodyB))
				{
					continue;
				}

				m_contactPair.push_back(ContactPair{ i, j });
			}
		}
	}

	void JWorld::NarrowPhase()
	{
		for(int i = 0; i < m_contactPair.size(); ++i)
		{
			ContactPair contactPair = m_contactPair[i];
			RigidBodyf* bodyA = m_rigidbodyList[contactPair.item1];
			RigidBodyf* bodyB = m_rigidbodyList[contactPair.item2];

			JMaths::Vector2Df normal{};
			float depth{ 0 };

			if (Collisions<float>::Collide(*bodyA,*bodyB, normal, depth))
			{
				SeparateBodies(*bodyA,*bodyB, normal, depth);

				JMaths::Vector2Df contact1;
				JMaths::Vector2Df contact2;
				float contactCount;

				Collisions<float>::FindContactPoints(*bodyA,*bodyB, contact1, contact2, contactCount);
				auto contact = Manifold<float>{ *bodyA, *bodyB, normal, depth, contact1, contact2, contactCount };
				ResolveCollision(contact);
			}

			//Manifold<float> contact = *m_contactList[i];
			

			/*if(contact.contactCount > 0)
			{
				if(std::find(m_contactPointsList.begin(), m_contactPointsList.end(), contact.contact1) == m_contactPointsList.end())
				{
					m_contactPointsList.push_back(contact.contact1);
				}

				if (contact.contactCount > 1)
				{
					if (std::find(m_contactPointsList.begin(), m_contactPointsList.end(), contact.contact2) == m_contactPointsList.end())
					{
						m_contactPointsList.push_back(contact.contact2);
					}
				}
			}*/
		}
	}

	void JWorld::ResolveCollision(Manifold<float>& _contact)
	{
		JMaths::Vector2Df relativeVelocity = _contact.bodyB.m_linearVelocity - _contact.bodyA.m_linearVelocity;

		if(relativeVelocity.dotProduct(_contact.normal) > 0.f)
		{
			return;
		}

		const float e = std::min(_contact.bodyA.restitution, _contact.bodyB.restitution);

		float j = -(1.f + e) * relativeVelocity.dotProduct(_contact.normal);
		j /= _contact.bodyA.invMass + _contact.bodyB.invMass;

		const JMaths::Vector2Df impluse = j * _contact.normal;

		_contact.bodyA.m_linearVelocity -= impluse * _contact.bodyA.invMass;
		_contact.bodyB.m_linearVelocity += impluse * _contact.bodyB.invMass;

	}

	void JWorld::SeparateBodies(RigidBodyf& _bodyA, RigidBodyf& _bodyB, const JMaths::Vector2Df& _normal, float& _depth)
	{
		if (_bodyA.isStatic)
		{
			_bodyB.Move(_normal * _depth);
		}
		else if (_bodyB.isStatic)
		{
			_bodyA.Move(JMaths::Vector2Df{ -_normal.x, -_normal.y } *(_depth / 2.f));
		}
		else
		{
			_bodyA.Move(JMaths::Vector2Df{ -_normal.x, -_normal.y } *(_depth / 2.f));
			_bodyB.Move(_normal * (_depth / 2.f));
		}
	}
}
