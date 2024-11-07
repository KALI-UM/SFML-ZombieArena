#include "stdafx.h"
#include "Effect.h"
#include "SceneGame.h"

Effect::Effect(const std::string& name)
	:SpriteGo("graphics/blood.png", name)
{
}

void Effect::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
	SpriteGo::Init();
}

void Effect::Reset()
{
	scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	SetOrigin(Origins::MC);
	timer = 0;
	SpriteGo::Reset();
}

void Effect::Update(float dt)
{
	timer += dt;
	if (timer >= duration)
	{
		scene->ReturnBlood(this);
	}
}
