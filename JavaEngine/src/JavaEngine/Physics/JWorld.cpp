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

	void JWorld::Step(float _time)
	{
		//Movement step
		for (int i = 0; i < m_rigidbodyList.size(); ++i)
		{
			m_rigidbodyList[i]->Step(_time);
		}

		//Collision step
		for (int i = 0; i < m_rigidbodyList.size() - 1; ++i)
		{
			RigidBodyf* bodyA = m_rigidbodyList[i];
			for (int j = 1; j < m_rigidbodyList.size(); ++j)
			{
				RigidBodyf* bodyB = m_rigidbodyList[j];

				if(bodyA == bodyB || bodyA->isStatic && bodyB->isStatic)
				{
					continue;
				}

				JMaths::Vector2Df normal{};
				float depth{ 0 };

				if(Collide(*bodyA, *bodyB, normal, depth))
				{
					if(bodyA->isStatic)
					{
						bodyB->Move(normal * depth);
					}else if(bodyB->isStatic)
					{
						bodyA->Move(JMaths::Vector2Df{ -normal.x, -normal.y } *(depth / 2.f));
					}else
					{
						bodyA->Move(JMaths::Vector2Df{ -normal.x, -normal.y } *(depth / 2.f));
						bodyB->Move(normal * (depth / 2.f));
					}

					ResolveCollision(*bodyA, *bodyB, normal, depth);
				}

				/*

				if (bodyA->shapeType == JPhysics::Box && bodyB->shapeType == JPhysics::Circle)
				{
					if (JPhysics::Collisions<float>::IntersectCirclePolygons(bodyB->GetPosition(), bodyB->radius, bodyA->GetTransformVertices(), normal, depth))
					{
						bodyB->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
						bodyA->Move(normal * (depth / 2.f));
					}
				}
				else if (bodyB->shapeType == JPhysics::Box && bodyA->shapeType == JPhysics::Circle)
				{
					if (JPhysics::Collisions<float>::IntersectCirclePolygons(bodyA->GetPosition(), bodyA->radius, bodyB->GetTransformVertices(), normal, depth))
					{
						bodyA->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
						bodyB->Move(normal * (depth / 2.f));
					}
				}*/


				/*if (JPhysics::Collisions<float>::IntersectPolygons(bodyA->GetTransformVertices(), bodyB->GetTransformVertices(), normal, depth))
				{
					JE_INFO("depth {0}", depth);
					bodyA->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
					bodyB->Move(normal * (depth / 2.f));
				}*/

				//if(JPhysics::Collisions<float>::IntersectCircles(
				//	bodyA->GetPosition(), bodyA->radius,
				//	bodyB->GetPosition(), bodyB->radius,
				//	normal, depth))
				//{
				//	JE_INFO("depth {0} {1}", normal.x, normal.y);
				//	bodyA->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
				//	bodyB->Move(normal * (depth / 2.f));
				//}
			}
		}
	}

	bool JWorld::Collide(const RigidBodyf& _bodyA, const RigidBodyf& _bodyB, JMaths::Vector2Df& _normal, float& _depth)
	{
		_normal = JMaths::Vector2Df::Zero;
		_depth = 0.f;

		ShapeType shapeTypeA = _bodyA.shapeType;
		ShapeType shapeTypeB = _bodyB.shapeType;

		RigidBodyf bodyA = _bodyA;
		RigidBodyf bodyB = _bodyB;

		if(shapeTypeA == ShapeType::Box)
		{
			if(shapeTypeB == ShapeType::Box)
			{
				return JPhysics::Collisions<float>::IntersectPolygons(bodyA.GetTransformVertices(), bodyB.GetTransformVertices(), _normal, _depth);
			}
			else if(shapeTypeB == ShapeType::Circle)
			{
				const bool result = JPhysics::Collisions<float>::IntersectCirclePolygons(bodyA.GetPosition(), bodyA.radius, bodyB.GetTransformVertices(), _normal, _depth);

				_normal = JMaths::Vector2Df{ -_normal.x, -_normal.y };
				return result;
			}
		}
		else if(shapeTypeA == ShapeType::Circle)
		{
			if (shapeTypeB == ShapeType::Box)
			{
				return JPhysics::Collisions<float>::IntersectCirclePolygons(bodyA.GetPosition(), bodyA.radius, bodyB.GetTransformVertices(), _normal, _depth);
			}
			else if (shapeTypeB == ShapeType::Circle)
			{
				return JPhysics::Collisions<float>::IntersectCircles(bodyA.GetPosition(), bodyA.radius, bodyB.GetPosition(), bodyB.radius, _normal, _depth);
			}
		}

		return false;
	}

	size_t JWorld::RigidbodyCount() const
	{
		return m_rigidbodyList.size();
	}

	void JWorld::ResolveCollision(RigidBodyf& _bodyA, RigidBodyf& _bodyB, JMaths::Vector2Df& _normal,
		float& depth)
	{
		JMaths::Vector2Df relativeVelocity = _bodyB.m_linearVelocity - _bodyA.m_linearVelocity;

		if(relativeVelocity.dotProduct(_normal) > 0.f)
		{
			return;
		}

		const float e = std::min(_bodyA.restitution, _bodyB.restitution);

		float j = -(1.f + e) * relativeVelocity.dotProduct(_normal);
		j /= _bodyA.invMass + _bodyB.invMass;

		const JMaths::Vector2Df impluse = j * _normal;

		_bodyA.m_linearVelocity -= impluse * _bodyA.invMass;
		_bodyB.m_linearVelocity += impluse * _bodyB.invMass;

	}
}
