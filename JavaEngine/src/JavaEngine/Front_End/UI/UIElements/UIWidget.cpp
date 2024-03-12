#include "UIWidget.h"


UIWidget::UIWidget(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name)
{

}

UIWidget::~UIWidget()
{
	for (UIElement* element : ChildElements) {
		//DELETE_PTR(element); delete all child
	}
}

void UIWidget::Draw(sf::RenderWindow& window) const
{
	for (UIElement* element : ChildElements) {
		element->Draw(window);
	}
}