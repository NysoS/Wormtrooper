#pragma once

#include "AABB.h"
#include "CircleCollider.h"
#include "jepch.h"
#include "PolygonCollider.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Vector2D.h"
#include "JavaEngine/Gameplay/Components/Transform.h"

namespace JPhysics
{
	constexpr float M_PI = 3.14f;
	static constexpr float MinBodySize = 0.01f * 0.01f;
	static constexpr float MaxBodySize = 64.f * 64.f;

	static constexpr float MinDensity = .5f;
	static constexpr float MaxDensity = 21.4f;

	enum ShapeType
	{
		Circle,
		Box
	};

	template<typename Type>
	class RigidBody : public JavaEngine::JObjectComponent
	{
	public:
		RigidBody() = default;

		RigidBody(const std::string& name,
			Type _density, Type _mass, Type _inertia, Type _resistution, Type area,
			bool _isStatic, ShapeType _shapeType,
			JavaEngine::ColliderBase* collider
		);
		virtual ~RigidBody() = default;

		static RigidBody* CreateCircleBody(Type _radius, Type _density,
			bool _isStatic, Type _resitution);

		static RigidBody* CreateBoxBody(Type _width, Type _height, Type _density,
			bool _isStatic, Type _resitution);

		JMaths::Vector2D<Type> GetPosition() const;
		Type GetRotation() const;

		static std::vector<JMaths::Vector2D<Type>> CreateBoxVertices(Type _width, Type _height);
		static std::vector<Type> CreateBoxTriangles();
		std::vector<JMaths::Vector2D<Type>> getTransformVertices();

		void Step(Type _time, const JMaths::Vector2D<Type>& _gravity, const Type& _iteratoons);
		void Move(JMaths::Vector2D<Type> _amount);
		void MoveTo(JMaths::Vector2D<Type> _position);
		void Rotate(Type _amount);
		void RotataTo(Type angle);
		void AddForce(JMaths::Vector2D<Type> _amount);

		AABB<Type> GetAABB();

	protected:
		JMaths::Vector2D<Type> m_position; //Transform
		Type m_angle; //Transform

		JMaths::Vector2D<Type> m_force;

		std::vector<JMaths::Vector2D<Type>> m_vertices;
		std::vector<Type> Triangles;
		std::vector<JMaths::Vector2D<Type>> m_transformVertices;

		bool m_transformUpdateRequired = false;

		AABB<Type> m_aabb;
		bool m_aabbUpdateRequired = false;

	public:
		Type mass;
		Type invMass = 0.f;
		Type density;
		Type restitution;
		Type area;
		Type inertia;
		Type invInertia = 0.f;

		bool isStatic;

		ShapeType shapeType;

		JMaths::Vector2D<Type> m_linearVelocity;
		Type angularVelocity;

		Type staticFriction;
		Type dynamicFriction;

		class JavaEngine::ColliderBase* collider;

	};

	template <typename Type>
	RigidBody<Type>::RigidBody(const std::string& name, Type _density, Type _mass, Type _inertia,
		Type _resistution, Type _area, bool _isStatic, ShapeType _shapeType, 
		JavaEngine::ColliderBase* collider)
			: JObjectComponent(name), m_position(JMaths::Vector2D<Type>::Zero), m_linearVelocity(JMaths::Vector2D<Type>::Zero), m_angle(0.f), angularVelocity(0.f), density(_density), mass(_mass), restitution(_resistution), area(_area), isStatic(_isStatic),
			shapeType(_shapeType), m_transformUpdateRequired(true), m_aabbUpdateRequired(true), m_aabb(AABB<Type>(0,0,0,0)), invMass(_mass > 0 ? 1.f / mass : 0.f), inertia(_inertia), invInertia(0.f),
			staticFriction(1.6f), dynamicFriction(1.4f), collider(collider)
	{
		m_force = JMaths::Vector2D<Type>::Zero;

		if(!_isStatic)
		{
			invInertia = 1.f/inertia;
		}

		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateCircleBody(Type _radius, Type _density,
		bool _isStatic, Type _resitution)
	{
		Type area = _radius * _radius * M_PI;

		if(_density < MinDensity || _density > MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = 0.f;
		Type inertia = 0.f;

		if (!_isStatic)
		{
			mass = area * _density;
			inertia = (1.f / 2) * mass * (_radius * _radius);
		}

		JavaEngine::ColliderBase* circleCollider = new JavaEngine::CircleCollider(_radius);

		return new RigidBody("Rigidbody", _density, mass, inertia, _resitution, area, _isStatic, ShapeType::Circle, circleCollider);
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateBoxBody(Type _width, Type _height,
		Type _density, bool _isStatic, Type _resitution)
	{
		Type area = _width * _height;

		if (_density < MinDensity || _density > MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = 0.f;
		Type inertia = 0.f;

		if(!_isStatic)
		{
			mass = area * _density;
			inertia = (1.f / 12) * mass * (_height * _height + _width * _width);
		}

		JavaEngine::ColliderBase* polygonCollider = new JavaEngine::PolygonCollider(_width, _height);

		return new RigidBody("Rigidbody", _density, mass, inertia, _resitution, area, _isStatic, ShapeType::Box, polygonCollider);
	}

	template <typename Type>
	JMaths::Vector2D<Type> RigidBody<Type>::GetPosition() const
	{
		return collider->position;
	}

	template <typename Type>
	Type RigidBody<Type>::GetRotation() const
	{
		return m_angle;
	}

	template <typename Type>
	std::vector<JMaths::Vector2D<Type>> RigidBody<Type>::CreateBoxVertices(Type _width, Type _height)
	{	
		Type left = - _width / 2.f;
		Type right = left + _width;
		Type bottom = - _height / 2.f;
		Type top = bottom + _height;

		return std::vector<JMaths::Vector2D<Type>>{
			JMaths::Vector2D<Type>{left, top},
			JMaths::Vector2D<Type>{right, top},
			JMaths::Vector2D<Type>{right, bottom},
			JMaths::Vector2D<Type>{left, bottom},
		};
	}

	template <typename Type>
	std::vector<Type> RigidBody<Type>::CreateBoxTriangles()
	{
		return std::vector<Type>{0, 1, 2, 0, 2, 3};
	}

	template <typename Type>
	std::vector<JMaths::Vector2D<Type>> RigidBody<Type>::getTransformVertices()
	{
		if(JavaEngine::PolygonCollider* polygonCollider = static_cast<JavaEngine::PolygonCollider*>(collider))
		{
			return polygonCollider->getTransformVertices();
		}

		return std::vector<JMaths::Vector2D<Type>>{};
	}

	template <typename Type>
	void RigidBody<Type>::Step(Type _time, const JMaths::Vector2D<Type>& _gravity, const Type& _iterations)
	{
		if(isStatic)
		{
			return;
		}

		Type time = _time / _iterations;

		//force = mass * acc
		//acc = force / mass

		//JMaths::Vector2D<Type> acceleration = m_force / mass;
		//m_linearVelocity += acceleration * _time;

		m_linearVelocity += _gravity * _time;
		m_linearVelocity += m_force;

		collider->position += m_linearVelocity * time;
		collider->angle += angularVelocity * time;

		m_force = JMaths::Vector2D<Type>::Zero;
		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Move(JMaths::Vector2D<Type> _amount)
	{
		collider->position.x += _amount.x;
		collider->position.y += _amount.y;
		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::MoveTo(JMaths::Vector2D<Type> _position)
	{
		collider->position = _position;
		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Rotate(Type _amount)
	{
		collider->angle += _amount;
		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::RotataTo(Type angle)
	{
		collider->angle = angle;
		collider->transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::AddForce(JMaths::Vector2D<Type> _amount)
	{
		m_force = _amount;
	}

	template <typename Type>
	AABB<Type> RigidBody<Type>::GetAABB()
	{
		if(m_aabbUpdateRequired)
		{
			Type minX = std::numeric_limits<Type>::max();
			Type minY = std::numeric_limits<Type>::max();
			Type maxX = std::numeric_limits<Type>::min();
			Type maxY = std::numeric_limits<Type>::min();

			if (shapeType == ShapeType::Box)
			{
				std::vector<JMaths::Vector2D<Type>> vertices = getTransformVertices();
				for (int i = 0; i < vertices.size(); ++i)
				{
					if (vertices[i].x < minX)
					{
						minX = vertices[i].x;
					}

					if (vertices[i].x > maxX)
					{
						maxX = vertices[i].x;
					}

					if (vertices[i].y < minY)
					{
						minY = vertices[i].y;
					}

					if (vertices[i].y > maxY)
					{
						maxY = vertices[i].y;
					}
				}

			}
			
			if(dynamic_cast<JavaEngine::CircleCollider*>(collider))
			{
				const JavaEngine::CircleCollider* circleCollider = dynamic_cast<JavaEngine::CircleCollider*>(collider);
				minX = collider->position.x - circleCollider->radius;
				minY = collider->position.y - circleCollider->radius;
				maxX = collider->position.x + circleCollider->radius;
				maxY = collider->position.y + circleCollider->radius;
			}

			m_aabb = AABB<Type>(minX, minY, maxX, maxY);
		}

		m_aabbUpdateRequired = false;
		return m_aabb;
	}

	using RigidBodyf = RigidBody<float>;
	using RigidBodyfPtr = RigidBody<float>*;
	using RigidBodyd = RigidBody<double>;
	using RigidBodydPtr = RigidBody<double>*;
	using RigidBodyi = RigidBody<int>;
	using RigidBodyiPtr = RigidBody<int>*;
}
