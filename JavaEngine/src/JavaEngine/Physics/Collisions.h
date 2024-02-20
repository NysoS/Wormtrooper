#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	template<typename Type>
	class JE_API Collisions
	{
	public:
		static bool IntersectCirclePolygons(
			const JMaths::Vector2D<Type>& _circlCenter, Type _circleRadius, const JMaths::Vector2D<Type>& _polygonCenter, const std::vector<JMaths::Vector2D<Type>>& _vertices,
			JMaths::Vector2D<Type>& _normal, Type& _depth
		);

		static bool IntersectCirclePolygons(
			const JMaths::Vector2D<Type>& _circlCenter, Type _circleRadius, const std::vector<JMaths::Vector2D<Type>>& _vertices,
			JMaths::Vector2D<Type>& _normal, Type& _depth
		);

		static bool IntersectPolygons(
			const JMaths::Vector2D<Type>& _centerA, const std::vector<JMaths::Vector2D<Type>>& _verticesA, 
			const JMaths::Vector2D<Type>& _centerB, const std::vector<JMaths::Vector2D<Type>>& _verticesB,
			JMaths::Vector2D<Type>& _normal, Type& _depth
		);

		static bool IntersectPolygons(
			const std::vector<JMaths::Vector2D<Type>>& _verticesA, const std::vector<JMaths::Vector2D<Type>>& _verticesB,
			JMaths::Vector2D<Type>& _normal, Type& _depth
		)
		{
			_normal = JMaths::Vector2D<Type>::Zero;
			_depth = std::numeric_limits<Type>::max();

			for(int i = 0; i < _verticesA.size(); ++i)
			{
				JMaths::Vector2D<Type> currentVerticesA = _verticesA[i];
				JMaths::Vector2D<Type> nextVerticesA = _verticesA[(i + 1) % _verticesA.size()];

				JMaths::Vector2D<Type> currentEdge = nextVerticesA - currentVerticesA;
				JMaths::Vector2D<Type> axis = currentEdge.GetLeftNormal();
				axis.normalilze();

				Type minA;
				Type maxA;
				Type minB;
				Type maxB;

				ProjectVertices(_verticesA, axis, minA, maxA);
				ProjectVertices(_verticesB, axis, minB, maxB);

				if(minA >= maxB || minB >= maxA)
				{
					return false;
				}

				Type axisDepth = std::min(maxB - minA, maxA - minB);
				if(axisDepth < _depth)
				{
					_depth = axisDepth;
					_normal = axis;
				}
			}

			for (int i = 0; i < _verticesB.size(); ++i)
			{
				JMaths::Vector2D<Type> currentVerticesB = _verticesB[i];
				JMaths::Vector2D<Type> nextVerticesB = _verticesB[(i + 1) % _verticesB.size()];

				JMaths::Vector2D<Type> currentEdge = nextVerticesB - currentVerticesB;
				JMaths::Vector2D<Type> axis = currentEdge.GetLeftNormal();
				axis.normalilze();

				Type minA;
				Type maxA;
				Type minB;
				Type maxB;

				ProjectVertices(_verticesA, axis, minA, maxA);
				ProjectVertices(_verticesB, axis, minB, maxB);

				if (minA >= maxB || minB >= maxA)
				{
					return false;
				}

				Type axisDepth = std::min(maxB - minA, maxA - minB);
				if (axisDepth < _depth)
				{
					_depth = axisDepth;
					_normal = axis;
				}
			}

			JMaths::Vector2D<Type> centerA = FindArithmeticMean(_verticesA);
			JMaths::Vector2D<Type> centerB = FindArithmeticMean(_verticesB);

			JMaths::Vector2D<Type> direction = centerB - centerA;
			if(direction.dotProduct(_normal) < 0.f)
			{
				_normal = JMaths::Vector2D<Type>{-_normal.x, -_normal.y};
			}

			return true;
		}

		static bool IntersectCircles(
			const JMaths::Vector2D<Type>& _centerA, const Type& _radiusA,
			const JMaths::Vector2D<Type>& _centerB, const Type& _radiusB,
			JMaths::Vector2D<Type>& _normal, Type& _depth)
		{
			_normal = JMaths::Vector2D<Type>::Zero;
			_depth = 0.f;

			Type distance = JMaths::Vector2D<Type>::Distance(_centerA, _centerB);
			Type radius = _radiusA + _radiusB;

			if(distance >= radius)
			{
				return false;
			}

			_normal = _centerB - _centerA;
			_normal.normalilze();

			_depth = radius - distance;

			return true;
		}

	private:
		static void ProjectVertices(const std::vector<JMaths::Vector2D<Type>>& _vertices, const JMaths::Vector2D<Type>& _axis, Type& _min, Type& _max);
		static void ProjectCircle(const JMaths::Vector2D<Type>& _center, const Type& _radius, const JMaths::Vector2D<Type>& _axis, Type& _min, Type& _max);
		static JMaths::Vector2D<Type> FindArithmeticMean(const std::vector<JMaths::Vector2D<Type>>& _vertices);
		static Type FindClosePointOnPolygon(const JMaths::Vector2D<Type>& _circleCenter, const std::vector<JMaths::Vector2D<Type>>& _vertices);
	};

	template <typename Type>
	bool Collisions<Type>::IntersectCirclePolygons(const JMaths::Vector2D<Type>& _circlCenter, Type _circleRadius,
		const JMaths::Vector2D<Type>& _polygonCenter, const std::vector<JMaths::Vector2D<Type>>& _vertices,
		JMaths::Vector2D<Type>& _normal, Type& _depth)
	{
		_normal = JMaths::Vector2D<Type>::Zero;
		_depth = std::numeric_limits<Type>::max();

		JMaths::Vector2D<Type> axis = JMaths::Vector2D<Type>::Zero;

		Type minA;
		Type maxA;
		Type minB;
		Type maxB;
		Type axisDepth = 0.f;

		for (int i = 0; i < _vertices.size(); ++i)
		{
			JMaths::Vector2D<Type> currentVerticesA = _vertices[i];
			JMaths::Vector2D<Type> nextVerticesA = _vertices[(i + 1) % _vertices.size()];

			JMaths::Vector2D<Type> currentEdge = nextVerticesA - currentVerticesA;
			axis = currentEdge.GetLeftNormal();
			axis.normalilze();

			ProjectVertices(_vertices, axis, minA, maxA);
			ProjectCircle(_circlCenter, _circleRadius, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < _depth)
			{
				_depth = axisDepth;
				_normal = axis;
			}
		}

		int cpIndex = FindClosePointOnPolygon(_circlCenter, _vertices);
		if (cpIndex <= -1.f)
		{
			return false;
		}

		JMaths::Vector2D<Type> cp = _vertices[cpIndex];
		axis = cp - _circlCenter;
		axis.normalilze();

		ProjectVertices(_vertices, axis, minA, maxA);
		ProjectCircle(_circlCenter, _circleRadius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}

		axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < _depth)
		{
			_depth = axisDepth;
			_normal = axis;
		}

		JMaths::Vector2D<Type> direction = _polygonCenter - _circlCenter;
		if (direction.dotProduct(_normal) < 0.f)
		{
			_normal = JMaths::Vector2D<Type>{ -_normal.x, -_normal.y };
		}

		return true;
	}

	template <typename Type>
	bool Collisions<Type>::IntersectCirclePolygons(const JMaths::Vector2D<Type>& _circlCenter, Type _circleRadius,
		const std::vector<JMaths::Vector2D<Type>>& _vertices, JMaths::Vector2D<Type>& _normal, Type& _depth)
	{
		_normal = JMaths::Vector2D<Type>::Zero;
		_depth = std::numeric_limits<Type>::max();

		JMaths::Vector2D<Type> axis = JMaths::Vector2D<Type>::Zero;

		Type minA;
		Type maxA;
		Type minB;
		Type maxB;
		Type axisDepth = 0.f;

		for (int i = 0; i < _vertices.size(); ++i)
		{
			JMaths::Vector2D<Type> currentVerticesA = _vertices[i];
			JMaths::Vector2D<Type> nextVerticesA = _vertices[(i + 1) % _vertices.size()];

			JMaths::Vector2D<Type> currentEdge = nextVerticesA - currentVerticesA;
			axis = currentEdge.GetLeftNormal();
			axis.normalilze();

			ProjectVertices(_vertices, axis, minA, maxA);
			ProjectCircle(_circlCenter, _circleRadius, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < _depth)
			{
				_depth = axisDepth;
				_normal = axis;
			}
		}

		int cpIndex = FindClosePointOnPolygon(_circlCenter, _vertices);
		if(cpIndex <= -1.f)
		{
			return false;
		}

		JMaths::Vector2D<Type> cp = _vertices[cpIndex];
		axis = cp - _circlCenter;
		axis.normalilze();

		ProjectVertices(_vertices, axis, minA, maxA);
		ProjectCircle(_circlCenter, _circleRadius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}

		axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < _depth)
		{
			_depth = axisDepth;
			_normal = axis;
		}

		JMaths::Vector2D<Type> polygonCenter = FindArithmeticMean(_vertices);

		JMaths::Vector2D<Type> direction = polygonCenter - _circlCenter;
		if (direction.dotProduct(_normal) < 0.f)
		{
			_normal = JMaths::Vector2D<Type>{ -_normal.x, -_normal.y };
		}

		return true;
	}

	template <typename Type>
	bool Collisions<Type>::IntersectPolygons(const JMaths::Vector2D<Type>& _centerA,
		const std::vector<JMaths::Vector2D<Type>>& _verticesA, const JMaths::Vector2D<Type>& _centerB,
		const std::vector<JMaths::Vector2D<Type>>& _verticesB, JMaths::Vector2D<Type>& _normal, Type& _depth)
	{
		_normal = JMaths::Vector2D<Type>::Zero;
		_depth = std::numeric_limits<Type>::max();

		for (int i = 0; i < _verticesA.size(); ++i)
		{
			JMaths::Vector2D<Type> currentVerticesA = _verticesA[i];
			JMaths::Vector2D<Type> nextVerticesA = _verticesA[(i + 1) % _verticesA.size()];

			JMaths::Vector2D<Type> currentEdge = nextVerticesA - currentVerticesA;
			JMaths::Vector2D<Type> axis = currentEdge.GetLeftNormal();
			axis.normalilze();

			Type minA;
			Type maxA;
			Type minB;
			Type maxB;

			ProjectVertices(_verticesA, axis, minA, maxA);
			ProjectVertices(_verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			Type axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < _depth)
			{
				_depth = axisDepth;
				_normal = axis;
			}
		}

		for (int i = 0; i < _verticesB.size(); ++i)
		{
			JMaths::Vector2D<Type> currentVerticesB = _verticesB[i];
			JMaths::Vector2D<Type> nextVerticesB = _verticesB[(i + 1) % _verticesB.size()];

			JMaths::Vector2D<Type> currentEdge = nextVerticesB - currentVerticesB;
			JMaths::Vector2D<Type> axis = currentEdge.GetLeftNormal();
			axis.normalilze();

			Type minA;
			Type maxA;
			Type minB;
			Type maxB;

			ProjectVertices(_verticesA, axis, minA, maxA);
			ProjectVertices(_verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			Type axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < _depth)
			{
				_depth = axisDepth;
				_normal = axis;
			}
		}

		JMaths::Vector2D<Type> direction = _centerB - _centerA;
		if (direction.dotProduct(_normal) < 0.f)
		{
			_normal = JMaths::Vector2D<Type>{ -_normal.x, -_normal.y };
		}

		return true;
	}

	template <typename Type>
	void Collisions<Type>::ProjectVertices(const std::vector<JMaths::Vector2D<Type>>& _vertices, const JMaths::Vector2D<Type>& _axis,
		Type& _min, Type& _max)
	{
		_min = std::numeric_limits<Type>::max();
		_max = std::numeric_limits<Type>::min();

		for(int i = 0; i < _vertices.size(); ++i)
		{
			JMaths::Vector2D<Type> vertices = _vertices[i];
			Type projection = vertices.dotProduct(_axis);

			if(projection < _min)
			{
				_min = projection;
			}

			if(projection > _max)
			{
				_max = projection;
			}
		}
	}

	template <typename Type>
	void Collisions<Type>::ProjectCircle(const JMaths::Vector2D<Type>& _center, const Type& _radius, const JMaths::Vector2D<Type>& _axis,
		Type& _min,Type& _max)
	{
		JMaths::Vector2D<Type> axis = _axis;
		JMaths::Vector2D<Type> direction = _axis.getNormarlized();
		JMaths::Vector2D<Type> radiusDirection = direction * _radius;

		JMaths::Vector2D<Type> pA = _center - radiusDirection;
		JMaths::Vector2D<Type> pB = _center + radiusDirection;

		_min = axis.dotProduct(pA);
		_max = axis.dotProduct(pB);

		if(_min > _max)
		{
			Type temp = _min;
			_min = _max;
			_max = temp;
		}
	}

	template <typename Type>
	JMaths::Vector2D<Type> Collisions<Type>::FindArithmeticMean(const std::vector<JMaths::Vector2D<Type>>& _vertices)
	{
		Type sumX = 0.f;
		Type sumY = 0.f;

		for(int i = 0; i < _vertices.size(); ++i)
		{
			JMaths::Vector2D<Type> vertices = _vertices[i];

			sumX += vertices.x;
			sumY += vertices.y;
		}

		return JMaths::Vector2D<Type>{sumX / _vertices.size(), sumY / _vertices.size()};
	}

	template <typename Type>
	Type Collisions<Type>::FindClosePointOnPolygon(const JMaths::Vector2D<Type>& _circleCenter,
		const std::vector<JMaths::Vector2D<Type>>& _vertices)
	{
		Type result = -1.f;
		Type minDistance = std::numeric_limits<Type>::max();

		for(int i = 0; i < _vertices.size(); i++)
		{
			JMaths::Vector2D<Type> vertices = _vertices[i];
			Type distance = JMaths::Vector2D<Type>::Distance(vertices, _circleCenter);

			if(distance < minDistance)
			{
				minDistance = distance;
				result = i;
			}
		}

		return result;
	}
}
