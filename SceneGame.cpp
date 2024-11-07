#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Item.h"
#include "ItemGenerator.h"
#include "ObjectPool.h"
#include "TileMap.h"
#include "UiHud.h"
#include "UiUpgrade.h"
#include "Effect.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	player = AddGo(new Player("Player"));
	background = AddGo(new TileMap());
	itemGenerator = AddGo(new ItemGenerator("ItemGenerator"));
	uiHud = AddGo(new UiHud());
	uiUpgrade = AddGo(new UiUpgrade());
	Scene::Init();
}

void SceneGame::Release()
{
	worldView.setCenter(0, 0);
	Scene::Release();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));

	Utils::SetOrigin(cursor, Origins::MC);
	SetStatus(Status::Awake);
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	background->SetOrigin(Origins::MC);
	UiView.setSize(size);
	UiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	Scene::Enter();
}

void SceneGame::Exit()
{
	ClearObjectPool();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;

	case Status::Upgrade:
		UpdateUpgrade(dt);
		break;

		break;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(cursor);
}

void SceneGame::SetStatus(Status status)
{
	Status prevStatus = currStatus;
	currStatus = status;

	switch (currStatus)
	{
	case Status::Awake:
		FRAMEWORK.SetTimeScale(0);
		uiHud->SetCenterMsg(true);
		uiUpgrade->SetActive(false);
		itemGenerator->SetActive(false);
		break;
	case Status::Game:
		player->SetMovableBounds(background->GetGlobalBounds());
		FRAMEWORK.SetTimeScale(1);
		uiHud->SetCenterMsg(false);
		uiHud->SetWave(currWave);
		itemGenerator->SetActive(true);
		zombieSpawnTimer = 0;
		if (prevStatus == Status::GameOver|| prevStatus == Status::Awake)
		{
			score = 0;
			player->Reset();
			itemGenerator->Reset();
			ClearObjectPool();
		}
		if (prevStatus == Status::Upgrade)
			ClearObjectPool();
		uiHud->SetScore(score);
		break;
	case Status::GameOver:
		FRAMEWORK.SetTimeScale(0);
		uiHud->SetHp(player->GetHp(), player->GetMaxHp());
		uiHud->SetCenterMsg(true);
		uiUpgrade->SetActive(false);
		itemGenerator->SetActive(false);
		if (score > highScore)
		{
			highScore = score;
			uiHud->SetHighScore(highScore);
		}
		currWave = 1;
		zombieSpawnTime = defaultSpawnTime;
		break;
	case Status::Upgrade:
		FRAMEWORK.SetTimeScale(0);
		uiUpgrade->SetActive(true);
		if (prevStatus == Status::GameOver || prevStatus == Status::Upgrade)
		{
			ClearObjectPool();
		}
		break;

		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		return;
	}
}

void SceneGame::UpdateGame(float dt)
{
	uiHud->SetZombieCount(zombies.size());
	uiHud->SetAmmo(player->GetAmmo(), player->GetMaxAmmo());
	uiHud->SetHp(player->GetHp(), player->GetMaxHp());

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SpawnZombies(3);
	//}

	zombieSpawnTimer += dt;
	if (zombieSpawnTimer > zombieSpawnTime)
	{
		SpawnZombies(10);
		zombieSpawnTimer = 0;
	}

	if (score > currWave * currWave * 100)
	{
		zombieSpawnTime *= 0.8f;
		SetStatus(Status::Upgrade);
	}
}

void SceneGame::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneGame::UpdateUpgrade(float dt)
{
	if (!uiUpgrade->IsActive())
	{
		currWave++;
		SetStatus(Status::Game);
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0; i < count; i++)
	{
		Zombie* zombie = zombiePool.Take();
		zombies.push_back(zombie);

		AddGo(zombie);
		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes - 1));
		auto tilebounds = background->GetGlobalBounds();
		zombie->SetPosition({ Utils::RandomRange(tilebounds.left, tilebounds.left + tilebounds.width), Utils::RandomRange(tilebounds.top, tilebounds.top + tilebounds.height) });
	}
}

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

Item* SceneGame::TakeItem()
{
	itemGenerator->SetSpawnBounds(background->GetGlobalBounds());
	Item* item = itemPool.Take();
	items.push_back(item);
	AddGo(item);
	return item;
}

void SceneGame::ReturnItem(Item* item)
{
	RemoveGo(item);
	itemPool.Return(item);
	items.remove(item);
}

Effect* SceneGame::TakeBlood()
{
	Effect* blood = bloodPool.Take();
	bloods.push_back(blood);
	AddGo(blood);
	return blood;
}

void SceneGame::ReturnBlood(Effect* blood)
{
	RemoveGo(blood);
	bloodPool.Return(blood);
	bloods.remove(blood);
}

void SceneGame::OnZombieDie(Zombie* zombie)
{
	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombies.remove(zombie);

	score += zombie->GetKillScore();
	uiHud->SetScore(score);
	auto blood = TakeBlood();
	blood->SetPosition(zombie->GetPosition());
	blood->SetRotation(zombie->GetRotation());
}

void SceneGame::ClearObjectPool()
{
	for (auto zombie : zombies)
	{
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();

	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();

	for (auto item : items)
	{
		RemoveGo(item);
		itemPool.Return(item);
	}
	items.clear();

	for (auto blood : bloods)
	{
		RemoveGo(blood);
		bloodPool.Return(blood);
	}
	bloods.clear();
}
