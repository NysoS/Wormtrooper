#include "JavaEngine/Gameplay/Components/JObjectComponent.h"

namespace JavaEngine
{
	JObjectComponent::JObjectComponent(const std::string& name)
	{
		m_Name = name;
	}

	std::string& JObjectComponent::GetName()
	{
		return m_Name;
	}
}
