#pragma once

class SceneGame;
class Effect : public SpriteGo
{
protected:
	float timer;
	float duration= 5;
	SceneGame* scene;
public:
	Effect(const std::string& name = "");
	~Effect() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};
