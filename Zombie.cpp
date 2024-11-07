#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "SceneGame.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<decltype(player)> (SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	body.setTexture(TEXTURE_MGR.Get(textureId[(int)this->type]));
	SetOrigin(Origins::MC);
	SetPosition({ 0, 0 });
	SetRotation(0);
	SetScale({ 1,1 });
	attackTimer = attackInterval;
}

void Zombie::Update(float dt)
{
	debug.SetRealBounds(body.getTransform(), GetLocalBounds());

	attackTimer += dt;
	if (player)
	{
		if (Utils::Distance(player->GetPosition(), GetPosition()) > 20)
		{
			debug.shape.setOutlineColor(sf::Color::Green);
			direction = Utils::GetNomalize(player->GetPosition() - GetPosition());
			SetRotation(Utils::Angle(direction));
			SetPosition(GetPosition() + direction * speed * dt);
		}

		if (player->GetGlobalBounds().intersects(GetGlobalBounds()))
		{
			if (Utils::CheckCollision(player->GetPlayerHitBox(), player->GetPlayerTransform(), body.getLocalBounds(), body.getTransform()))
			{
				debug.shape.setOutlineColor(sf::Color::Magenta);
				if (attackTimer > attackInterval)
				{
					debug.shape.setOutlineColor(sf::Color::Red);
					OnAttack();
					attackTimer = 0;
				}
			}
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debug.Draw(window);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
	{
		speed = 100.f;
		maxHp = 50.f;
		damage = 10.f;
		killscore = 25;
		break;
	}
	case Types::Chaser:
	{
		speed = 75.0f;
		maxHp = 20.f;
		damage = 5.f;
		killscore = 10;
		break;
	}
	case Types::Crawler:
	{
		speed = 50.0f;
		maxHp = 10.f;
		damage = 20.f;
		killscore = 5;
		break;
	}
	break;
	}

	hp = maxHp;
	body.setTexture(TEXTURE_MGR.Get(textureId[(int)this->type]), true);
}

void Zombie::OnDamage(int damage)
{
	hp -= damage;
	if (hp <= 0 && scene)
	{
		scene->OnZombieDie(this);
	}
}

void Zombie::OnAttack()
{
	player->OnDamaged(damage);
}
