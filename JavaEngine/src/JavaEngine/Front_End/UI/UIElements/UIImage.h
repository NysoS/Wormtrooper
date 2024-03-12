#pragma once

#include "../UIElement.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>


class UIImage : public UIElement
{
public:

	explicit UIImage(sf::Vector2f size);
	UIImage(UIElement& parent, sf::Vector2f size, std::string& name);

	~UIImage() override;

	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;
	void Draw(sf::RenderWindow& window) const override;

	void SetTexture(sf::Texture& texture);
	void SwitchTexture(sf::Texture& newTexture);
	void SetColor(sf::Color& color);

	sf::Vector2f GetSpriteSize() const;



private:
	sf::Sprite Sprite;
	sf::Color ImageColor;

};