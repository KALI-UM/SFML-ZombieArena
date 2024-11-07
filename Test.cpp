#include "stdafx.h"
#include "Test.h"

Test::Test(const std::string& name)
	: GameObject(name)
{
}

void Test::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Test::SetRotation(float angle)
{
	rotation = angle;
}

void Test::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Test::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Test::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Test::Init()
{
}

void Test::Release()
{
}

void Test::Reset()
{
}

void Test::Update(float dt)
{
}

void Test::Draw(sf::RenderWindow& window)
{
}
