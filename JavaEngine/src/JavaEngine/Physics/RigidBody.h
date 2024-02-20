#pragma once

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
			JMaths::Vector2D<Type> _position, Type _density, Type _mass, Type _resistution, Type area,
			bool _isStatic, Type _radius, Type _width, Type _height, ShapeType _shapeType
		);
		virtual ~RigidBody() = default;

		static RigidBody* CreateCircleBody(Type _radius, JMaths::Vector2D<Type> _position, Type _density,
			bool _isStatic, Type _resitution);

		static RigidBody* CreateBoxBody(Type _width, Type _height, JMaths::Vector2D<Type> _position, Type _density,
			bool _isStatic, Type _resitution);

		JMaths::Vector2D<Type> GetPosition() const;
		Type GetRotation() const;

		static std::vector<JMaths::Vector2D<Type>> CreateBoxVertices(Type _width, Type _height);
		static std::vector<Type> CreateBoxTriangles();
		std::vector<JMaths::Vector2D<Type>> GetTransformVertices();

		void Step(Type _time, const JMaths::Vector2D<Type>& _gravity);
		void Move(JMaths::Vector2D<Type> _amount);
		void MoveTo(JMaths::Vector2D<Type> _position);
		void Rotate(Type _amount);
		void AddForce(JMaths::Vector2D<Type> _amount);

	protected:
		JMaths::Vector2D<Type> m_position;
		Type m_rotation;
		Type m_rotationVelocity;

		JMaths::Vector2D<Type> m_force;

		std::vector<JMaths::Vector2D<Type>> m_vertices;
		std::vector<Type> Triangles;
		std::vector<JMaths::Vector2D<Type>> m_transformVertices;

		bool m_transformUpdateRequired = false;

	public:
		Type mass;
		Type invMass = 0.f;
		Type density;
		Type restitution;
		Type area;

		bool isStatic;

		Type radius;
		Type width;
		Type height;

		ShapeType shapeType;

		JMaths::Vector2D<Type> m_linearVelocity;
	};

	template <typename Type>
	RigidBody<Type>::RigidBody(JMaths::Vector2D<Type> _position, Type _density, Type _mass,
		Type _resistution, Type _area, bool _isStatic, Type _radius, Type _width, Type _height, ShapeType _shapeType)
			: m_position(_position), m_linearVelocity(JMaths::Vector2D<Type>::Zero), m_rotation(0.f), m_rotationVelocity(0.f), density(_density), mass(_mass), restitution(_resistution), area(_area), isStatic(_isStatic),
			radius(_radius), width(_width), height(_height), shapeType(_shapeType)
	{
		if(shapeType == ShapeType::Box)
		{
			m_vertices = CreateBoxVertices(width, height);
			m_transformVertices.resize(m_vertices.size());
		}

		m_transformUpdateRequired = true;
		m_force = JMaths::Vector2D<Type>::Zero;

		if(!isStatic)
		{
			invMass = 1.f / mass;
		}
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateCircleBody(Type _radius, JMaths::Vector2D<Type> _position, Type _density,
		bool _isStatic, Type _resitution)
	{
		Type area = _radius * _radius * M_PI;
		/*if(area < MinBodySize || area > MaxBodySize)
		{
			return nullptr;
		}*/

		if(_density < MinDensity || _density > MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = area * _density;

		return new RigidBody(_position, _density, mass, _resitution, area, _isStatic, _radius, 0.f, 0.f, ShapeType::Circle);
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateBoxBody(Type _width, Type _height, JMaths::Vector2D<Type> _position,
		Type _density, bool _isStatic, Type _resitution)
	{
		Type area = _width * _height;
		/*if (area < MinBodySize || area > MaxBodySize)
		{
			return nullptr;
		}*/

		if (_density < MinDensity || _density > MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = area * _density;

		return new RigidBody(_position, _density, mass, _resitution, area, _isStatic, 0.f, _width, _height, ShapeType::Box);
	}

	template <typename Type>
	JMaths::Vector2D<Type> RigidBody<Type>::GetPosition() const
	{
		return m_position;
	}

	template <typename Type>
	Type RigidBody<Type>::GetRotation() const
	{
		return m_rotation;
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
			transform->setRotation(m_rotation);

			for(int i = 0; i < m_vertices.size(); ++i)
			{
				JMaths::Vector2D<Type> vector = m_vertices[i];
				m_transformVertices[i] = transform->vector(vector);
			}
		}

		return m_transformVertices;
	}

	template <typename Type>
	void RigidBody<Type>::Step(Type _time, const JMaths::Vector2D<Type>& _gravity)
	{
		if(isStatic)
		{
			return;
		}

		//force = mass * acc
		//acc = force / mass

		//JMaths::Vector2D<Type> acceleration = m_force / mass;
		//m_linearVelocity += acceleration * _time;

		m_linearVelocity += _gravity * _time;

		m_position += m_linearVelocity * _time;
		m_rotation += m_rotationVelocity * _time;

		m_force = JMaths::Vector2D<Type>::Zero;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Move(JMaths::Vector2D<Type> _amount)
	{
		m_position.x += _amount.x;
		m_position.y += _amount.y;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::MoveTo(JMaths::Vector2D<Type> _position)
	{
		m_position = _position;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Rotate(Type _amount)
	{
		m_rotation += _amount;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::AddForce(JMaths::Vector2D<Type> _amount)
	{
		m_force = _amount;
	}

	using RigidBodyf = RigidBody<float>;
	using RigidBodyfPtr = RigidBody<float>*;
	using RigidBodyd = RigidBody<double>;
	using RigidBodydPtr = RigidBody<double>*;
	using RigidBodyi = RigidBody<int>;
	using RigidBodyiPtr = RigidBody<int>*;
}
