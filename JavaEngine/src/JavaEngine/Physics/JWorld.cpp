#include "JavaEngine/Physics/JWorld.h"

#include "Collisions.h"
#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Core/Dispatcher/FnDispatcher.h"
#include "JavaEngine/Physics/ColliderIntersect.h"

namespace JPhysics
{
	JWorld::JWorld()
		: m_gravity(JMaths::Vector2Df(0, 9.81f)), m_colliderIntersect(new ColliderIntersect<float>), m_contactPoints(new ContactPoints<float>)
	{
		fnDispatcher.add<JavaEngine::CircleCollider, JavaEngine::CircleCollider>(m_colliderIntersect.get(), &ColliderIntersect<float>::OnCircleColliderIntersectCallback);
		fnDispatcher.add<JavaEngine::PolygonCollider, JavaEngine::PolygonCollider>(m_colliderIntersect.get(), &ColliderIntersect<float>::OnPolygonColliderIntersectCallback);
		fnDispatcher.add<JavaEngine::CircleCollider, JavaEngine::PolygonCollider>(m_colliderIntersect.get(), &ColliderIntersect<float>::OnCircleToPolygonColliderIntersectCallback);
		fnDispatcher.add<JavaEngine::PolygonCollider, JavaEngine::CircleCollider>(m_colliderIntersect.get(), &ColliderIntersect<float>::OnPolygonToCircleColliderIntersectCallback);

		contactPointsDispatcher.add<JavaEngine::CircleCollider, JavaEngine::CircleCollider>(m_contactPoints.get(), &ContactPoints<float>::OnCircleContactPointsCallback);
		contactPointsDispatcher.add<JavaEngine::PolygonCollider, JavaEngine::PolygonCollider>(m_contactPoints.get(), &ContactPoints<float>::OnPolygonContactPointsCallback);
		contactPointsDispatcher.add<JavaEngine::CircleCollider, JavaEngine::PolygonCollider>(m_contactPoints.get(), &ContactPoints<float>::OnCircleToPolygonContactPointsCallback);
		contactPointsDispatcher.add<JavaEngine::PolygonCollider, JavaEngine::CircleCollider>(m_contactPoints.get(), &ContactPoints<float>::OnPolygonToCirlceContactPointsCallback);
	}

	JWorld::~JWorld()
	{
		for(auto* rbody : m_rigidbodyList)
		{
			delete rbody;
			rbody = nullptr;
		}
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
		delete _rigidbody;
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

			const IntersectInfo<float> m_intersectInfo = fnDispatcher(*bodyA->collider, *bodyB->collider);
			normal = m_intersectInfo.normal;
			depth = m_intersectInfo.depth;

			if (m_intersectInfo.isIntersect)
			{
				SeparateBodies(*bodyA,*bodyB, normal, depth);

				const ContactPointsInfo<float> m_contactPointsInfo = contactPointsDispatcher(*bodyA->collider, *bodyB->collider);
				
				auto contact = Manifold<float>{ *bodyA, *bodyB, normal, depth, m_contactPointsInfo.contact1, m_contactPointsInfo.contact2, m_contactPointsInfo.contactCount };
				ResolveCollisionWithRotation(contact);
			}
		}
	}

	void JWorld::ResolveCollisionBasic(Manifold<float>& _contact)
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

	void JWorld::ResolveCollisionWithRotation(Manifold<float>& _contact)
	{
		const float e = std::min(_contact.bodyA.restitution, _contact.bodyB.restitution);
		JMaths::Vector2Df contactList[2] = { _contact.contact1, _contact.contact2 };
		JMaths::Vector2Df impulseList[2] = {JMaths::Vector2Df{}, JMaths::Vector2Df{} };
		JMaths::Vector2Df raList[2] = { JMaths::Vector2Df{}, JMaths::Vector2Df{} };
		JMaths::Vector2Df rbList[2] = { JMaths::Vector2Df{}, JMaths::Vector2Df{} };

		const int contactCount = static_cast<int>(_contact.contactCount);

		for(int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df ra = contactList[i] - _contact.bodyA.collider->position;
			JMaths::Vector2Df rb = contactList[i] - _contact.bodyB.collider->position;

			raList[i] = ra;
			rbList[i] = rb;

			JMaths::Vector2Df raPerp = ra.GetLeftNormal();
			JMaths::Vector2Df rbPerp = rb.GetLeftNormal();

			JMaths::Vector2Df angularLinearVelocityBodyA = raPerp * _contact.bodyA.angularVelocity;
			JMaths::Vector2Df angularLinearVelocityBodyB = rbPerp * _contact.bodyB.angularVelocity;
			 
			JMaths::Vector2Df relativeVelocity = (_contact.bodyB.m_linearVelocity + angularLinearVelocityBodyB) - (_contact.bodyA.m_linearVelocity + angularLinearVelocityBodyA);

			float contactVelocityMag = relativeVelocity.dotProduct(_contact.normal);

			if (relativeVelocity.dotProduct(_contact.normal) > 0.f)
			{
				continue;
			}

			float raPerpDotN = raPerp.dotProduct(_contact.normal);
			float rbPerpDotN = rbPerp.dotProduct(_contact.normal);

			float denom = _contact.bodyA.invMass + _contact.bodyB.invMass + 
				(raPerpDotN * raPerpDotN) * _contact.bodyA.invInertia + 
				(rbPerpDotN * rbPerpDotN) * _contact.bodyB.invInertia;

			float j = -(1.f + e) * contactVelocityMag;
			j /= denom;
			j /= _contact.contactCount;

			const JMaths::Vector2Df impluse = j * _contact.normal;
			impulseList[i] = impluse;
		}

		for(int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df impulse = impulseList[i];
			JMaths::Vector2Df ra = raList[i];
			JMaths::Vector2Df rb = rbList[i];

			_contact.bodyA.m_linearVelocity -= impulse * _contact.bodyA.invMass;
			_contact.bodyA.angularVelocity += -JMaths::Vector2Df::Cross(ra, impulse) * _contact.bodyA.invInertia;
			_contact.bodyB.m_linearVelocity += impulse * _contact.bodyB.invMass;
			_contact.bodyB.angularVelocity += JMaths::Vector2Df::Cross(rb, impulse) * _contact.bodyB.invInertia;
		}
	}

	void JWorld::ResolveCollisionWithRotationAndFriction(Manifold<float>& _contact)
	{
		const float e = std::min(_contact.bodyA.restitution, _contact.bodyB.restitution);
		contactList[0] = _contact.contact1;
		contactList[1] = _contact.contact2;

		float sf = (_contact.bodyA.staticFriction +_contact.bodyB.staticFriction) * 0.5f;
		float df = (_contact.bodyA.dynamicFriction + _contact.bodyB.dynamicFriction) * 0.5f;

		const int contactCount = static_cast<int>(_contact.contactCount);

		for(int i = 0; i < contactCount; ++i)
		{
			impulseList[i] = JMaths::Vector2Df::Zero;
			raList[i] = JMaths::Vector2Df::Zero;
			rbList[i] = JMaths::Vector2Df::Zero;
			impulseFrictionList[i] = JMaths::Vector2Df::Zero;
			jList[i] = 0.f;
		}

		for (int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df ra = contactList[i] - _contact.bodyA.GetPosition();
			JMaths::Vector2Df rb = contactList[i] - _contact.bodyB.GetPosition();

			raList[i] = ra;
			rbList[i] = rb;

			JMaths::Vector2Df raPerp = ra.GetLeftNormal();
			JMaths::Vector2Df rbPerp = rb.GetLeftNormal();

			JMaths::Vector2Df angularLinearVelocityBodyA = raPerp * _contact.bodyA.angularVelocity;
			JMaths::Vector2Df angularLinearVelocityBodyB = rbPerp * _contact.bodyB.angularVelocity;

			JMaths::Vector2Df relativeVelocity = (_contact.bodyB.m_linearVelocity + angularLinearVelocityBodyB) - (_contact.bodyA.m_linearVelocity + angularLinearVelocityBodyA);

			float contactVelocityMag = relativeVelocity.dotProduct(_contact.normal);

			if (relativeVelocity.dotProduct(_contact.normal) > 0.8f)
			{
				continue;
			}

			float raPerpDotN = raPerp.dotProduct(_contact.normal);
			float rbPerpDotN = rbPerp.dotProduct(_contact.normal);

			float denom = _contact.bodyA.invMass + _contact.bodyB.invMass +
				(raPerpDotN * raPerpDotN) * _contact.bodyA.invInertia +
				(rbPerpDotN * rbPerpDotN) * _contact.bodyB.invInertia;

			float j = -(1.f + e) * contactVelocityMag;
			j /= denom;
			j /= _contact.contactCount;

			jList[i] = j;

			const JMaths::Vector2Df impluse = j * _contact.normal;
			impulseList[i] = impluse;
		}

		for (int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df impulse = impulseList[i];
			JMaths::Vector2Df ra = raList[i];
			JMaths::Vector2Df rb = rbList[i];

			_contact.bodyA.m_linearVelocity += JMaths::Vector2Df(-impulse.x, -impulse.y) * _contact.bodyA.invMass;
			_contact.bodyA.angularVelocity += -JMaths::Vector2Df::Cross(ra, impulse) * _contact.bodyA.invInertia;
			_contact.bodyB.m_linearVelocity += impulse * _contact.bodyB.invMass;
			_contact.bodyB.angularVelocity += JMaths::Vector2Df::Cross(rb, impulse) * _contact.bodyB.invInertia;
		}

		//Friction
		for (int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df ra = contactList[i] - _contact.bodyA.GetPosition();
			JMaths::Vector2Df rb = contactList[i] - _contact.bodyB.GetPosition();

			raList[i] = ra;
			rbList[i] = rb;

			JMaths::Vector2Df raPerp = ra.GetLeftNormal();
			JMaths::Vector2Df rbPerp = rb.GetLeftNormal();

			JMaths::Vector2Df angularLinearVelocityBodyA = raPerp * std::round(_contact.bodyA.angularVelocity);
			JMaths::Vector2Df angularLinearVelocityBodyB = rbPerp * std::round(_contact.bodyB.angularVelocity);

			JMaths::Vector2Df relativeVelocity = (_contact.bodyB.m_linearVelocity + angularLinearVelocityBodyB) - (_contact.bodyA.m_linearVelocity + angularLinearVelocityBodyA);

			JMaths::Vector2Df tangent = relativeVelocity - relativeVelocity.dotProduct(_contact.normal) * _contact.normal;

			if (JMaths::JMath<float>::NearlyEqual(tangent, JMaths::Vector2Df::Zero))
			{
				continue;
			}
			tangent.normalilze();

			float raPerpDotT = raPerp.dotProduct(tangent);
			float rbPerpDotT = rbPerp.dotProduct(tangent);

			float denom = _contact.bodyA.invMass + _contact.bodyB.invMass +
				(raPerpDotT * raPerpDotT) * _contact.bodyA.invInertia +
				(rbPerpDotT * rbPerpDotT) * _contact.bodyB.invInertia;

			float jt = -relativeVelocity.dotProduct(tangent);
			jt /= denom;
			jt /= contactCount;

			JMaths::Vector2Df impulseFriction;
			if(std::abs(jt) <= jList[i] * sf)
			{
				impulseFriction = jt * tangent;
			}else
			{
				impulseFriction = -jList[i] * tangent * df;
			}
			
			impulseFrictionList[i] = impulseFriction;
		}

		for (int i = 0; i < contactCount; ++i)
		{
			JMaths::Vector2Df impulseFriction = impulseFrictionList[i];
			JMaths::Vector2Df ra = raList[i];
			JMaths::Vector2Df rb = rbList[i];

			_contact.bodyA.m_linearVelocity -= impulseFriction * _contact.bodyA.invMass;
			_contact.bodyA.angularVelocity += -JMaths::Vector2Df::Cross(ra, impulseFriction) * _contact.bodyA.invInertia;
			_contact.bodyB.m_linearVelocity += impulseFriction * _contact.bodyB.invMass;
			_contact.bodyB.angularVelocity += JMaths::Vector2Df::Cross(rb, impulseFriction) * _contact.bodyB.invInertia;
		}
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
