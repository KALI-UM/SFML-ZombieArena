#pragma once

class Player;
class SceneGame;
class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes=3;
protected:
	Types type = Types::Bloater;
	
	sf::Sprite body;
	std::string textureId[3] = { "graphics/bloater.png", "graphics/crawler.png", "graphics/chaser.png" };

	sf::Vector2f direction;
	int maxHp;
	float speed = 100;
	float attackInterval =5;

	int hp;
	float attackTimer=0;
	int damage;
	int killscore=10;
	Player* player;
	SceneGame* scene;
	DebugBox debug;
public:
	Zombie(const std::string& name = "");
	~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
	void OnDamage(int damage);
	void OnAttack();

	int GetKillScore()const { return killscore; }
};
