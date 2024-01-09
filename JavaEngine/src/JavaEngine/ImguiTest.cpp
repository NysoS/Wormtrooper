#include "jepch.h"

#include "ImguiTest.h"

#include <imgui.h>
#include "Core.h"

namespace JavaEngine
{
	 ImguiTest::ImguiTest()
	{
		
	}

	 ImguiTest::~ImguiTest()
	{
		
	}

	void ImguiTest::Draw()
	{
		ImGui::Begin("Try imgui");
		ImGui::Text("This is text imgui into JavaEngine");
		ImGui::End();
	};
}