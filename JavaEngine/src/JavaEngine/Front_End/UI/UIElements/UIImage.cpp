#include "UIImage.h"

namespace JavaEngine
{
	UIImage::UIImage(sf::Vector2f size) : UIElement(size)
	{

	}

	UIImage::UIImage(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name)
	{

	}

	UIImage::~UIImage()
	{

	}

	void UIImage::SetPosition(float positionX, float positionY)
	{
		UIElement::SetPosition(positionX, positionY);
		Sprite.setPosition(Position);
	}

	void UIImage::SetScale(float scaleX, float scaleY)
	{
		UIElement::SetScale(scaleX, scaleY);
		Sprite.setScale(scaleX, scaleY);
		Size = sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height);
	}

	void UIImage::SetTexture(sf::Texture& texture)
	{
		Sprite.setTexture(texture);
		Size.x = Sprite.getGlobalBounds().width;
		Size.y = Sprite.getGlobalBounds().height;
	}

	void UIImage::SwitchTexture(sf::Texture& newTexture)
	{
		Sprite.setTexture(newTexture);
	}

	void UIImage::SetColor(sf::Color& color)
	{
		Sprite.setColor(color);
	}

	sf::Vector2f UIImage::GetSpriteSize() const
	{
		return sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height);
	}

	void UIImage::Draw(sf::RenderWindow& window) const
	{
		window.draw(Sprite);
	}
}