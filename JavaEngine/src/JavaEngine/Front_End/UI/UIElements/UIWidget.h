#pragma once

#include "..\UIElement.h"


class UIWidget : public UIElement
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
		Element* element = newElement(*this, Size, nameElement);
		ChildElements.push_back(element);
		return element;
	}

private:
	std::vector<UIElement*> ChildElements;
};

