#include "UIText.h"

UIText::UIText(sf::Vector2f size) : UIElement(size)
{
	SetFontSize(20);
}

UIText::UIText(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name)
{
	SetFontSize(20);
}

UIText::~UIText()
{

}

void UIText::Draw(sf::RenderWindow& window) const
{
	window.draw(Text);
}

void UIText::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	Text.setPosition(positionX, positionY);
}

void UIText::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	Text.setScale(scaleX, scaleY);
	Size = sf::Vector2f(Text.getGlobalBounds().width, Text.getGlobalBounds().height);
}

void UIText::SetString(std::string& text)
{
	Text.setString(text);
	Size = sf::Vector2f(Text.getGlobalBounds().width, Text.getGlobalBounds().height);
}

void UIText::SetFont(sf::Font& font)
{
	Text.setFont(font);
}

void UIText::SetFontSize(float size)
{
	Text.setCharacterSize(size);
}
