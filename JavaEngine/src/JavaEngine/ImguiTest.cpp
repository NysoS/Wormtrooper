#include "jepch.h"
#include "Core.h"
#include "imgui.h"

namespace JavaEngine
{
	class JE_API ImguiTest
	{
		ImguiTest()
		{
			
		}

		~ImguiTest()
		{
			
		}

		void Draw()
		{
			ImGui::Begin("Try imgui");
			ImGui::Text("This is text imgui into JavaEngine");
			ImGui::End();
		}
	};
}