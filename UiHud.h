#pragma once

class TextGo;
class UiHud : public GameObject
{
protected:
	sf::Text textPressEnter;

	sf::Text textScore;
	sf::Text textHighScore;
	sf::Sprite iconAmmo;
	sf::Text textAmmo;
	sf::Text textWave;
	sf::Text textZombieCount;
	sf::RectangleShape gaugeHp;
	sf::RectangleShape maxHpBar;

	sf::Vector2f gaugeHpMaxSize = { 400, 50 };


public:
	UiHud(const std::string& name = "");
	~UiHud() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetScore(int s);
	void SetHighScore(int s);
	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);

	void SetCenterMsg(bool show);

};
