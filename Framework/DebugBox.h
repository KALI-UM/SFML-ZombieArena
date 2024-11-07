#pragma once

class DebugBox
{
public:
	sf::RectangleShape shape;

	DebugBox();

	void SetBounds(const sf::FloatRect& bounds);
	void SetRealBounds(const sf::Transform& trans, const sf::FloatRect& localBounds);

	static void SetVisible(bool v);
	static bool IsVisible();

	void Draw(sf::RenderWindow& window);
private:
	static bool isVisible;
	sf::Transform transform;
};