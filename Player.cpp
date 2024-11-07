#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	SetOrigin(Origins::MC);

	body.setTexture(TEXTURE_MGR.Get(textureId));
	speed = defaultSpeed;

	SetOrigin(originPreset);
	SetRotation(0);
	SetPosition({ 0, 0 });
}

void Player::Release()
{
}

void Player::Reset()
{
	/*dynamic_cast<decltype(sceneGame)>*/
	sceneGame = (SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));

	SetOrigin(originPreset);
	SetRotation(30);
	SetPosition({ 0, 0 });

	shootDelay = defaultShootDelay;
	shootTimer = defaultShootDelay;
	hitBox = body.getLocalBounds();

	speed = defaultSpeed;
	reloadTimer = reloadDlay;
	hp = defaultHp;
	maxHp = defaultHp;
	maxAmmo = defaultAmmo;
	ammo = defaultAmmo;
}

void Player::Update(float dt)
{
	debug.SetRealBounds(body.getTransform(), GetLocalBounds());

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.0f)
		Utils::Nomalize(direction);

	sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition();
	if (sceneGame)
	{
		mousePos = sceneGame->ScreenToWorld({ (int)mousePos.x, (int)mousePos.y });
	}
	look = sf::Vector2f(mousePos - position);
	SetRotation(Utils::Angle(look));
	sf::Vector2f prevPos = position;
	SetPosition(position + dt * speed * direction);
	SetPosition({ Utils::Clamp(position.x, movableBounds.left, movableBounds.left + movableBounds.width),
				Utils::Clamp(position.y, movableBounds.top, movableBounds.top + movableBounds.height) });
	shootTimer += dt;
	reloadTimer += dt;

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		reloadTimer = 0;
		ammo = maxAmmo;
	}

	if (reloadTimer >= reloadDlay)
	{
		if (ammo != 0 && shootTimer > shootDelay && InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			Shoot();
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debug.Draw(window);
}

void Player::Shoot()
{
	Bullet* bullet = dynamic_cast<SceneGame*>(sceneGame)->TakeBullet();
	bullet->Fire(position, look, 300, 50);
	shootTimer = 0;
	ammo--;
}

void Player::OnGetHealpack(int hp)
{
	this->hp += hp;
	this->hp = Utils::Clamp(this->hp, 0, maxHp);
}

void Player::OnGetAmmo()
{
	shootDelay *= 0.8f;
}

void Player::OnDamaged(int damage)
{
	if (this->hp <= 0)
	{
		return;
	}

	this->hp -= damage;
	this->hp = Utils::Clamp(this->hp, 0, maxHp);
	if (this->hp <= 0)
	{
		OnDie();
	}
}

void Player::OnDie()
{
	dynamic_cast<SceneGame*>(sceneGame)->SetStatus(Status::GameOver);
	Reset();
}

void Player::SetMovableBounds(const sf::FloatRect& rect)
{
	movableBounds = rect;
}
