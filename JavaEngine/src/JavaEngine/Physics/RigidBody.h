#pragma once

#include "AABB.h"
#include "jepch.h"
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
	class JE_API RigidBody
	{
	public:
		RigidBody() = default;

		RigidBody(
			Type _density, Type _mass, Type _inertia, Type _resistution, Type area,
			bool _isStatic, Type _radius, Type _width, Type _height, std::vector<JMaths::Vector2D<Type>> _vertices, ShapeType _shapeType
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
		std::vector<JMaths::Vector2D<Type>> GetTransformVertices();

		void Step(Type _time, const JMaths::Vector2D<Type>& _gravity, const Type& _iteratoons);
		void Move(JMaths::Vector2D<Type> _amount);
		void MoveTo(JMaths::Vector2D<Type> _position);
		void Rotate(Type _amount);
		void RotataTo(Type angle);
		void AddForce(JMaths::Vector2D<Type> _amount);

		AABB<Type> GetAABB();

	protected:
		JMaths::Vector2D<Type> m_position;
		Type m_angle;
		Type m_angleVelocity;

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
		Type invInertia;

		bool isStatic;

		Type radius;
		Type width;
		Type height;

		ShapeType shapeType;

		JMaths::Vector2D<Type> m_linearVelocity;
	};

	template <typename Type>
	RigidBody<Type>::RigidBody(Type _density, Type _mass, Type _inertia,
		Type _resistution, Type _area, bool _isStatic, Type _radius, 
		Type _width, Type _height, std::vector<JMaths::Vector2D<Type>> _vertices, ShapeType _shapeType)
			: m_position(JMaths::Vector2D<Type>::Zero), m_linearVelocity(JMaths::Vector2D<Type>::Zero), m_angle(0.f), m_angleVelocity(0.f), density(_density), mass(_mass), restitution(_resistution), area(_area), isStatic(_isStatic),
			radius(_radius), width(_width), height(_height), shapeType(_shapeType), m_transformUpdateRequired(true), m_aabbUpdateRequired(true), m_aabb(AABB<Type>(0,0,0,0)), invMass(_mass > 0 ? 1.f / mass : 0.f), inertia(_inertia), invInertia(_inertia > 0 ? 1.f / inertia : 0.f)
	{
		if(shapeType == ShapeType::Box)
		{
			m_vertices = _vertices;
			m_transformVertices.resize(m_vertices.size());
		}

		m_force = JMaths::Vector2D<Type>::Zero;

		m_transformUpdateRequired = true;
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

		return new RigidBody(_density, mass, inertia, _resitution, area, _isStatic, _radius, 0.f, 0.f, std::vector<JMaths::Vector2D<Type>>{}, ShapeType::Circle);
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

		std::vector<JMaths::Vector2D<Type>> vertices = CreateBoxVertices(_width, _height);

		return new RigidBody(_density, mass, inertia, _resitution, area, _isStatic, 0.f, _width, _height, vertices, ShapeType::Box);
	}

	template <typename Type>
	JMaths::Vector2D<Type> RigidBody<Type>::GetPosition() const
	{
		return m_position;
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
	std::vector<JMaths::Vector2D<Type>> RigidBody<Type>::GetTransformVertices()
	{
		if(m_transformUpdateRequired)
		{
			JavaEngine::Transform<Type>* transform = new JavaEngine::Transform<Type>();
			transform->setPosition(m_position);
			transform->setRotation(m_angle);

			for(int i = 0; i < m_vertices.size(); ++i)
			{
				JMaths::Vector2D<Type> vector = m_vertices[i];
				m_transformVertices[i] = transform->vector(vector);
			}
		}

		return m_transformVertices;
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

		m_linearVelocity += _gravity * time;

		m_position += m_linearVelocity * time;
		m_angle += m_angleVelocity * time;

		m_force = JMaths::Vector2D<Type>::Zero;
		m_transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Move(JMaths::Vector2D<Type> _amount)
	{
		m_position.x += _amount.x;
		m_position.y += _amount.y;
		m_transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::MoveTo(JMaths::Vector2D<Type> _position)
	{
		m_position = _position;
		m_transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Rotate(Type _amount)
	{
		m_angle += _amount;
		m_transformUpdateRequired = true;
		m_aabbUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::RotataTo(Type angle)
	{
		m_angle = angle;
		m_transformUpdateRequired = true;
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
				std::vector<JMaths::Vector2D<Type>> vertices = GetTransformVertices();
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
			else if (shapeType == ShapeType::Circle)
			{
				minX = m_position.x - radius;
				minY = m_position.y - radius;
				maxX = m_position.x + radius;
				maxY = m_position.y + radius;
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
