#include "stdafx.h"
#include "UiUpgrade.h"
#include "Player.h"
#include "ItemGenerator.h"

UiUpgrade::UiUpgrade(const std::string& name)
	: GameObject(name)
{
}

void UiUpgrade::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 200;
}

void UiUpgrade::Release()
{
}

void UiUpgrade::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	itemGenerator = dynamic_cast<ItemGenerator*>(SCENE_MGR.GetCurrentScene()->FindGo("ItemGenerator"));
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));

	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	int fontSize = 80;
	for (int i = 0; i < 6; i++)
	{
		auto& text = textButton[i];
		text.setFont(font);
		text.setCharacterSize(80);
		text.setString(str[i]);
		text.setFillColor(sf::Color::White);
		Utils::SetOrigin(text, Origins::TL);
		text.setPosition(size.x / 5, size.y / 3 + 80 * i);
	}

	upgradeFunc[0] = [&]() {player->shootDelay *= 0.8f; };
	upgradeFunc[1] = [&]() {player->maxAmmo += 5; };
	upgradeFunc[2] = [&]() {player->maxHp += 10; };
	upgradeFunc[3] = [&]() {player->speed += 100; };
	upgradeFunc[4] = [&]() {itemGenerator->SetSpawnDelay(0, itemGenerator->GetSpawnDelay(0) * 0.8f); };
	upgradeFunc[5] = [&]() {itemGenerator->SetSpawnDelay(1, itemGenerator->GetSpawnDelay(1) * 0.8f); };
}

void UiUpgrade::Update(float dt)
{
}

void UiUpgrade::FixedUpdate(float dt)
{
	sf::Vector2f mousepos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());
	for (int i = 0; i < 6; i++)
	{
		auto& text = textButton[i];
		if (Utils::PointInTransformBounds(text, text.getLocalBounds(), mousepos))
		{
			text.setFillColor(sf::Color::Yellow);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				Upgrade(i);
				Reset();
				SetActive(false);
				break;
			}
		}
		else
		{
			text.setFillColor(sf::Color::White);
		}
	}
}

void UiUpgrade::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (auto& text : textButton)
	{
		window.draw(text);
	}
}

void UiUpgrade::Upgrade(int index)
{
	upgradeFunc[index]();
}
