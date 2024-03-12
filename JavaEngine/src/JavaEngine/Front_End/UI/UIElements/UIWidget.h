#pragma once
#include "JavaEngine/Front_End/UI/UIElement.h"
#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	class JE_API UIWidget : public JavaEngine::UIElement
	{
	public:

		//UIWidget(sf::Vector2f size);
		UIWidget(UIElement& parent, sf::Vector2f size, std::string& name);

		~UIWidget() override;

		void Draw(sf::RenderWindow& window) const override;

		template <typename Element>
		Element* addElement(std::string nameElement)
		{
			if (!std::is_base_of<UIElement, Element>())
			{
				return nullptr;
			}
			Element* element = new Element(*this, Size, nameElement);
			ChildElements.push_back(element);
			return element;
		}

	private:
		std::vector<UIElement*> ChildElements;
	};
}
