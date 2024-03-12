#pragma once
#include <SFML/Graphics.hpp>

class UIElement
{
public:
	sf::Vector2f Size;
	sf::Vector2f Position;
	sf::Vector2f Scale;

	UIElement* ParentElement = nullptr;
	std::string Name;

	explicit UIElement(sf::Vector2f size);
	UIElement(UIElement& parent, sf::Vector2f size, std::string& name);
	virtual ~UIElement();

	virtual void Draw(sf::RenderWindow& window) const = 0;

	virtual void SetParent(UIElement& parent);
	virtual void SetPosition(float positionX, float positionY);
	virtual void SetScale(float scaleX, float scaleY);


};

