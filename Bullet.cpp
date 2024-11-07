#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textrueId));
	SetOrigin(Origins::ML);
	SetPosition({ 0,0 });
	SetRotation(0);
	SetScale({ 1,1 });

	direction = { 0,0 };
	speed = 0;
	damage = 0;
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	debug.SetBounds(GetGlobalBounds());
}

void Bullet::FixedUpdate(float dt)
{
	if (!scene)return;

	const auto& list = scene->GetZombieList();
	for (auto zombie : list)
	{
		if (!zombie->IsActive())
			continue;

		sf::FloatRect bounds = GetGlobalBounds();
		sf::FloatRect zombieBounds = zombie->GetGlobalBounds();
		if (bounds.intersects(zombieBounds))
		{
			zombie->OnDamage(damage);
			scene->ReturnBullet(this);
			break;
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debug.Draw(window);
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f dir, float s, int d)
{
	SetPosition(pos);
	direction = Utils::GetNomalize(dir);
	speed = s;
	damage = d;
	SetRotation(Utils::Angle(direction));
}
