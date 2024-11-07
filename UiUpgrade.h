#pragma once

class Player;
class ItemGenerator;
class UiUpgrade : public GameObject
{
protected:
	sf::Sprite background;

	sf::Text textButton[6];
	std::string str[6] = 
	{"1. INCREASE RATE OF FIRE",
	"2. INCREASE CLIP SIZE (NEXT RELOAD)",
	"3. INCREASE MAX HEALTH",
	"4. INCREASE RUN SPEED",
	"5. MORE AND BETTER HEALTH PICKUPS",
	"6. MORE AND BETTER AMMO PICKUPS"};

	Player* player;
	ItemGenerator* itemGenerator;
	std::function<void()> upgradeFunc[6];
public:
	UiUpgrade(const std::string& name = "");
	~UiUpgrade() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Upgrade(int index);
	
};
