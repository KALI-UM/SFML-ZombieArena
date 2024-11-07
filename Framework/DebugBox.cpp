#include "stdafx.h"
#include "DebugBox.h"

bool DebugBox::isVisible = true;
DebugBox::DebugBox()
{
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);
}

void DebugBox::SetBounds(const sf::FloatRect& bounds)
{
	transform = sf::Transform::Identity;
	shape.setSize({ bounds.width, bounds.height });
	shape.setPosition(bounds.left, bounds.top);
}

void DebugBox::SetRealBounds(const sf::Transform& trans, const sf::FloatRect& localBounds)
{
	transform = trans;
	shape.setSize({ localBounds.width, localBounds.height });
	shape.setPosition(0, 0);
}

void DebugBox::SetVisible(bool v)
{
	isVisible = v;
}

bool DebugBox::IsVisible()
{
	return isVisible;
}

void DebugBox::Draw(sf::RenderWindow& window)
{
	if(isVisible)
	window.draw(shape, transform);
}
