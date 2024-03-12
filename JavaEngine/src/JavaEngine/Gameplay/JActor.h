#pragma once

#include "jepch.h"
#include "JObject.h"
#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	class JE_API JActor : public JObject
	{
	public:
		JActor(JPhysics::JWorld* world);
		~JActor() override;

		void Update() override;
	};
}