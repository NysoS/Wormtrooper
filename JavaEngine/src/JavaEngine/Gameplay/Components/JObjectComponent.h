#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

#include <iostream>;

namespace JavaEngine
{
	class JE_API JObjectComponent
	{
	public:
		explicit JObjectComponent(const std::string& name = std::string("Component"));
		virtual ~JObjectComponent() = default;

		std::string& GetName();

	protected:
		std::string m_Name;
	};
}
