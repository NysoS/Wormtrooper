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
			//Movement step
			for (int i = 0; i < m_rigidbodyList.size(); ++i)
			{
				m_rigidbodyList[i]->Step(_time, m_gravity, static_cast<float>(iterations));
			}

			m_contactList.clear();

			//Collision step
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

					JMaths::Vector2Df normal{};
					float depth{ 0 };

					if(!Collisions<float>::IntersectAABB(aabb_bodyA, aabb_bodyB))
					{
						continue;
					}

					if (Collisions<float>::Collide(*bodyA, *bodyB, normal, depth))
					{
						if (bodyA->isStatic)
						{
							bodyB->Move(normal * depth);
						}
						else if (bodyB->isStatic)
						{
							bodyA->Move(JMaths::Vector2Df{ -normal.x, -normal.y } *(depth / 2.f));
						}
						else
						{
							bodyA->Move(JMaths::Vector2Df{ -normal.x, -normal.y } *(depth / 2.f));
							bodyB->Move(normal * (depth / 2.f));
						}


						JMaths::Vector2Df contact1;
						JMaths::Vector2Df contact2;
						float contactCount;

						Collisions<float>::FindContactPoints(*bodyA, *bodyB, contact1, contact2, contactCount);
						Manifold<float>* c = new Manifold<float>{ *bodyA, *bodyB, normal, depth, contact1, contact2, contactCount };
						m_contactList.push_back(c);
					}
				}
			}

			for(int i = 0; i < m_contactList.size(); ++i)
			{
				Manifold<float> contact = *m_contactList[i];
				ResolveCollision(contact);

				if(contact.contactCount > 0)
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
				}
			}
		}
	}

	size_t JWorld::RigidbodyCount() const
	{
		return m_rigidbodyList.size();
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
}
