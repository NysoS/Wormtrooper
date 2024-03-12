#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"


namespace JavaEngine
{
	class JE_API ColliderBase
	{
	public:
		explicit ColliderBase(const JMaths::Vector2Df& pos = JMaths::Vector2Df::Zero, float angle = 0);
		virtual ~ColliderBase();

		JMaths::Vector2Df position;
		float angle;
		bool transformUpdateRequired = true;
	};
}
