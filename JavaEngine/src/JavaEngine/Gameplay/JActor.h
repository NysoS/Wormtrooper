#pragma once

#include "jepch.h"
#include "JObject.h"
#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	class JE_API JActor : public JObject
	{
	public:
		JActor();
		virtual ~JActor();

		void Update() override;
	};
}