#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	float textSize = 50.f;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	textPressEnter.setFont(font);
	textPressEnter.setCharacterSize(textSize*2);
	textPressEnter.setFillColor(sf::Color::White);
	textPressEnter.setString("PRESS ENTER\nTO CONTINUE");
	Utils::SetOrigin(textPressEnter, Origins::MC);

	textScore.setFont(font);
	textScore.setCharacterSize(textSize);
	textScore.setFillColor(sf::Color::White);
	Utils::SetOrigin(textScore, Origins::TL);

	textHighScore.setFont(font);
	textHighScore.setCharacterSize(textSize);
	textHighScore.setFillColor(sf::Color::White);
	Utils::SetOrigin(textHighScore, Origins::TR);

	textAmmo.setFont(font);
	textAmmo.setCharacterSize(textSize);
	textAmmo.setFillColor(sf::Color::White);
	Utils::SetOrigin(textAmmo, Origins::BL);

	textWave.setFont(font);
	textWave.setCharacterSize(textSize);
	textWave.setFillColor(sf::Color::White);
	Utils::SetOrigin(textWave, Origins::BR);

	textZombieCount.setFont(font);
	textZombieCount.setCharacterSize(textSize);
	textZombieCount.setFillColor(sf::Color::White);
	Utils::SetOrigin(textZombieCount, Origins::BR);

	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpMaxSize);
	Utils::SetOrigin(gaugeHp, Origins::BL);

	maxHpBar.setFillColor(sf::Color::White);
	//maxHpBar.setOutlineColor(sf::Color::White);
	//maxHpBar.setOutlineThickness(3);
	maxHpBar.setSize(gaugeHpMaxSize);
	Utils::SetOrigin(maxHpBar, Origins::BL);

	iconAmmo.setTexture(TEXTURE_MGR.Get("graphics/ammo_icon.png"));
	Utils::SetOrigin(iconAmmo, Origins::BL);

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	float topY = 25.f;
	float BottomY = size.y - 100.f;

	textPressEnter.setPosition(size.x / 2, size.y / 2);
	textPressEnter.setFillColor(sf::Color::Transparent);

	textScore.setPosition(25.f, topY);
	textHighScore.setPosition(size.x - 25.f, topY);

	iconAmmo.setPosition(25.f, BottomY);
	gaugeHp.setPosition(300.f, BottomY);
	maxHpBar.setPosition(300.f, BottomY);
	textAmmo.setPosition(100.f, BottomY);

	textWave.setPosition(size.x - 400.f, BottomY);
	textZombieCount.setPosition(size.x - 25.f, BottomY);


	SetScore(0);
	SetHighScore(0);
	SetAmmo(0, 0);
	SetHp(1.f, 1.f);
	SetWave(0);
	SetZombieCount(0);
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(iconAmmo);
	window.draw(maxHpBar);
	window.draw(gaugeHp);
	window.draw(textAmmo);
	window.draw(textWave);
	window.draw(textZombieCount);
	window.draw(textPressEnter);
}

void UiHud::SetScore(int s)
{
	textScore.setString("SCORE: " + std::to_string(s));
	Utils::SetOrigin(textScore, Origins::TL);
}

void UiHud::SetHighScore(int s)
{
	textHighScore.setString("HI SCORE: " + std::to_string(s));
	Utils::SetOrigin(textHighScore, Origins::TR);
}

void UiHud::SetAmmo(int current, int total)
{
	textAmmo.setString(std::to_string(current) + " / " + std::to_string(total));
	Utils::SetOrigin(textAmmo, Origins::BL);
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpMaxSize.x * value, gaugeHpMaxSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.setString("WAVE: " + std::to_string(w));
	Utils::SetOrigin(textWave, Origins::BR);
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.setString("ZOMBIES: " + std::to_string(count));
	Utils::SetOrigin(textZombieCount, Origins::BR);
}

void UiHud::SetCenterMsg(bool show)
{
	if(show)
	textPressEnter.setFillColor(sf::Color::White);
	else
	textPressEnter.setFillColor(sf::Color::Transparent);
}
