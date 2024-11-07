#pragma once

class Player;
class Item : public SpriteGo
{
protected:
	std::function<void(Player*)> itemEffect;
	sf::FloatRect collider;
	Player* player;
public:
	Item(const std::string& name = "");
	~Item() = default;

	void Reset() override;
	void Update(float dt) override;
	void SetItemEffect(std::function<void(Player*)> effectfunc, const std::string& texId);
};
