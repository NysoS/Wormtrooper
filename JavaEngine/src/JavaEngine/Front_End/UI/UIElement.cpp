#include "UIElement.h"


namespace JavaEngine
{
	UIElement::UIElement(sf::Vector2f size) : Size(size), Position(0, 0), ParentElement(nullptr), Scale(1.f, 1.f)
	{
	}

	UIElement::UIElement(UIElement& parent, sf::Vector2f size, std::string& name) : ParentElement(&parent), Size(size), Name(name), Position(0, 0), Scale(1.f, 1.f)
	{
	}

	UIElement::~UIElement()
	{
	}

	void UIElement::SetParent(UIElement& parent)
	{
		ParentElement = &parent;
	}

	void UIElement::SetPosition(float positionX, float positionY)
	{

		sf::Vector2f parentPosition{ 0,0 };
		sf::Vector2f parentSize{ 0, 0 };
		if (&ParentElement) {
			parentPosition = ParentElement->Position;
			parentSize = ParentElement->Size;
		}

		Position = sf::Vector2f(parentPosition.x + positionX, parentPosition.y + positionY);
	}

	void UIElement::SetScale(float scaleX, float scaleY)
	{
		sf::Vector2f parentSize{ 0, 0 };
		if (&ParentElement) {
			parentSize = ParentElement->Size;
		}
		Scale = sf::Vector2f(scaleX, scaleY);
	}
}
