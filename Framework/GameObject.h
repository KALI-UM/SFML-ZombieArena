#pragma once

class GameObject
{
protected:
	std::string name;
	
	bool active = true;

	sf::Vector2f position;
	sf::Vector2f scale = {1.0f,1.0f};
	float rotation;

	Origins originPreset;
	sf::Vector2f origin;

public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	float GetRotation() const { return rotation; }
	virtual void SetRotation(float angle) { rotation = angle; }

	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& scale) { this->scale = scale; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual sf::FloatRect GetLocalBounds() const { return { 0.0f,0.0f,0.0f,0.0f }; }
	virtual sf::FloatRect GetGlobalBounds() const { return { 0.0f,0.0f,0.0f,0.0f }; }

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		return a->sortingOrder > b->sortingOrder;
	}
};

