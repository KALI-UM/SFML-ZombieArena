#pragma once
class Scene;
class UiUpgrade;
class Player : public GameObject
{
private:
	friend class UiUpgrade;
protected:
	sf::Sprite body;
	std::string textureId = "graphics/player.png";
	float defaultSpeed= 100;
	float speed= defaultSpeed;
	sf::Vector2f direction;
	sf::Vector2f look;

	int defaultHp = 100;
	int maxHp = defaultHp;
	int hp = maxHp;

	int defaultAmmo = 5;
	int maxAmmo = defaultAmmo;
	int ammo = maxAmmo;

	float defaultShootDelay = 0.5f;
	float shootDelay = defaultShootDelay;
	float shootTimer = shootDelay;
	float reloadDlay = 0.5;
	float reloadTimer = reloadDlay;

	Scene* sceneGame;

	sf::FloatRect hitBox;
	sf::FloatRect movableBounds;
	DebugBox debug;
public:
	Player(const std::string& name = "");
	~Player() = default;

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

	void Shoot();
	void OnGetHealpack(int hp);
	void OnGetAmmo();
	void OnDamaged(int damage);
	void OnDie();

	void SetMovableBounds(const sf::FloatRect& rect);

	int GetHp()const { return hp; }
	int GetMaxHp()const { return maxHp; }
	int GetAmmo()const { return ammo; }
	int GetMaxAmmo()const { return maxAmmo; }

	const sf::Sprite& GetPlayerSprite() { return body; }
	const sf::FloatRect& GetPlayerHitBox() { return hitBox; }
	const sf::Transform& GetPlayerTransform() { return body.getTransform(); }
};
