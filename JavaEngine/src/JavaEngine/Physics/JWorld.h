#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

namespace JPhysics
{
	class JE_API JWorld
	{
	public:
		static constexpr float MinBodySize = 0.01f * 0.01f;
		static constexpr float MaxBodySize = 64.f * 64.f;

		static constexpr float MinDensity = .5f;
		static constexpr float MaxDensity = 21.4f;
	};
}
