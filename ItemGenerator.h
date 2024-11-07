#pragma once

class Player;
class ItemGenerator : public GameObject
{
public:
	enum class ItemType
	{
		Health,
		Ammo,
	};

	struct ItemInfo
	{
		ItemType type;
		std::string texid;
		std::function<void(Player*)> effect;
	};

protected:
	std::vector<ItemInfo> itemInfo;
	float itemDefaultDelay[2] = { 5.0f,5.0f };
	float itemSpawnTimer[2] = { 0.0f,0.0f };
	float itemSpawnDelay[2] = { 5.0f,5.0f };
	sf::FloatRect spawnBounds;
public:
	ItemGenerator(const std::string& name = "");
	~ItemGenerator() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void SetSpawnBounds(const sf::FloatRect& rect);
	void SetSpawnDelay(int index, float value);
	float GetSpawnDelay(int index) const { return itemSpawnDelay[index]; }
};

