#pragma once

#include "jepch.h"
#include "Vector2D.h"
#include "JavaEngine/Core/Core.h"

namespace JMaths
{
	template <typename Type>
	using Vec2D = Vector2D<Type>;

	template <typename Type>
	struct JE_API VectorProjectionInfo
	{
		Type min = .0f;
		Type max = .0f;
	};

	template <typename Type>
	struct JE_API VectorProjection
	{
		VectorProjectionInfo<Type> polygonProjection(const std::vector<Vec2D<Type>>& vertices, const Vec2D<Type>& axis)
		{
			VectorProjectionInfo<Type> vectorProjectionInfo{};
			vectorProjectionInfo.min = std::numeric_limits<Type>::max();
			vectorProjectionInfo.max = std::numeric_limits<Type>::min();

			for (int i = 0; i < vertices.size(); ++i)
			{
				Vec2D<Type> vertice = vertices[i];
				Type projection = vertice.dotProduct(axis);

				if (projection < vectorProjectionInfo.min)
				{
					vectorProjectionInfo.min = projection;
				}

				if (projection > vectorProjectionInfo.max)
				{
					vectorProjectionInfo.max = projection;
				}
			}

			return vectorProjectionInfo;
		}

		VectorProjectionInfo<Type> circleProjection(const Vec2D<Type>& center, const Type& radius, const Vec2D<Type>& projectionAxis)
		{
			VectorProjectionInfo<Type> vectorProjectionInfo{};

			Vec2D<Type> axis = projectionAxis;
			Vec2D<Type> direction = axis.getNormarlized();
			Vec2D<Type> radiusDirection = direction * radius;

			Vec2D<Type> pA = center - radiusDirection;
			Vec2D<Type> pB = center + radiusDirection;

			vectorProjectionInfo.min = axis.dotProduct(pA);
			vectorProjectionInfo.max = axis.dotProduct(pB);

			if (vectorProjectionInfo.min > vectorProjectionInfo.max)
			{
				Type temp = vectorProjectionInfo.min;
				vectorProjectionInfo.min = vectorProjectionInfo.max;
				vectorProjectionInfo.max = temp;
			}

			return vectorProjectionInfo;
		}
	};
}