#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "SceneGame.h"

Item::Item(const std::string& name)
	: SpriteGo("graphics/health_pickup.png", name)
{
}

void Item::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	SetOrigin(Origins::MC);
	SpriteGo::Reset();
}

void Item::Update(float dt)
{
	collider = GetGlobalBounds();
	if (player&&collider.contains(player->GetPosition()))
	{
		itemEffect(player);
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->ReturnItem(this);
	}
	SpriteGo::Update(dt);
}

void Item::SetItemEffect(std::function<void(Player*)> effectfunc, const std::string& texId)
{
	SetTextureId(texId);
	itemEffect = effectfunc;
	Reset();
}

