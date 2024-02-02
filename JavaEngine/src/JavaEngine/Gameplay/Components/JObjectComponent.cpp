#include "JavaEngine/Gameplay/Components/JObjectComponent.h"

namespace JavaEngine
{
	JObjectComponent::JObjectComponent()
	{
	}

	std::string& JObjectComponent::GetName()
	{
		return m_Name;
	}
}
