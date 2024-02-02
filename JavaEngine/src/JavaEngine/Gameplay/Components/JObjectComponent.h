#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

#include <iostream>;

namespace JavaEngine
{
	class JE_API JObjectComponent
	{
	public:
		JObjectComponent();

		std::string& GetName();

	protected:
		std::string m_Name;
	};
}
