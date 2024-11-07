#pragma once
#include "Scene.h"
class Player;
class Zombie;
class Bullet;
class ItemGenerator;
class Item;
class TileMap;
class Effect;
class UiHud;
class UiUpgrade;
enum class Status
{
	Awake,
	Game,
	GameOver,
	Upgrade,
};
class SceneGame :
	public Scene
{
public:

protected:
	Player* player;
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;
	ItemGenerator*		itemGenerator;
	std::list<Item*>	items;
	ObjectPool<Item>	itemPool;

	TileMap* background;

	std::list<Effect*>	bloods;
	ObjectPool<Effect>	bloodPool;

	UiHud* uiHud;
	UiUpgrade* uiUpgrade;
	int score = 0;
	int highScore = 0;
	Status currStatus = Status::Awake;
	int currWave = 1;
	float defaultSpawnTime = 3;
	float zombieSpawnTime = defaultSpawnTime;
	float zombieSpawnTimer = 0;
public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Release()override;
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;

	void SetStatus(Status status);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdateUpgrade(float dt);

	void SpawnZombies(int count);
	Bullet* TakeBullet();
	void ReturnBullet(Bullet* bullet);
	Item* TakeItem();
	void ReturnItem(Item* item);
	Effect* TakeBlood();
	void ReturnBlood(Effect* blood);

	const std::list<Zombie*>& GetZombieList() { return zombies; };
	void OnZombieDie(Zombie* zombie);

private:
	void ClearObjectPool();
};

