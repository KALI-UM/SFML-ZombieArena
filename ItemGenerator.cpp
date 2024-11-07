#include "stdafx.h"
#include "ItemGenerator.h"
#include "SceneGame.h"
#include "Item.h"
#include "Player.h"

ItemGenerator::ItemGenerator(const std::string& name)
	:GameObject(name)
{
}

void ItemGenerator::Init()
{
	itemInfo.resize(2);
	itemInfo[0].type = ItemType::Health;
	itemInfo[0].texid = "graphics/health_pickup.png";
	itemInfo[0].effect = [&](Player* player) {player->OnGetHealpack(10); };
	itemInfo[1].type = ItemType::Ammo;
	itemInfo[1].texid = "graphics/ammo_pickup.png";
	itemInfo[1].effect = [&](Player* player) {player->OnGetAmmo(); };

	itemSpawnTimer[0] = 0;
	itemSpawnTimer[1] = 0;
}

void ItemGenerator::Reset()
{
	itemSpawnDelay[0] = itemDefaultDelay[0];
	itemSpawnDelay[1] = itemDefaultDelay[1];
	itemSpawnTimer[0] = 0;
	itemSpawnTimer[1] = 0;
}

void ItemGenerator::Update(float dt)
{
	for (int i = 0; i < 2; i++)
	{
		itemSpawnTimer[i] += dt;
		if (itemSpawnTimer[i] > itemSpawnDelay[i])
		{
			auto item = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->TakeItem();
			int itemIndex = Utils::RandomRange(0, 1);
			item->SetItemEffect(itemInfo[itemIndex].effect, itemInfo[itemIndex].texid);
			sf::Vector2f pos;
			pos.x = Utils::RandomRange(spawnBounds.left, spawnBounds.left + spawnBounds.width);
			pos.y = Utils::RandomRange(spawnBounds.top, spawnBounds.top + spawnBounds.height);
			item->SetPosition(pos);
			itemSpawnTimer[i] = 0;
		}
	}
}

void ItemGenerator::SetSpawnBounds(const sf::FloatRect& rect)
{
	spawnBounds = rect;
}

void ItemGenerator::SetSpawnDelay(int index, float value)
{
	itemSpawnDelay[index] = value;
}
