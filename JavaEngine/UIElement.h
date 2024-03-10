#pragma once
class UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	virtual void Draw();

	virtual void SetParent();
	virtual void SetPosition();
	virtual void SetScale();
};

