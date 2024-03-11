
#include "../UIElement.h"
#include <SFML/Graphics/Text.hpp>
#include <string>

class UIText : public UIElement
{
	explicit UIText(sf::Vector2f size);
	UIText(UIElement& parent, sf::Vector2f size, std::string& name);

	~UIText() override;

	void Draw(sf::RenderWindow& window) const override;
	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;

	void SetString(std::string& text);
	void SetFont(sf::Font& font);
	void SetFontSize(float fontSize);

protected:
	sf::Text Text;

};
