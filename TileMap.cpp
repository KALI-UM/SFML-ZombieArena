#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::GetOriginValue(originPreset,va.getBounds());
	}
	
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
}

sf::FloatRect TileMap::GetLocalBounds() const
{
	return { 0,0,(float)cellSize.x * cellCount.x, (float)cellSize.y * cellCount.y };
}

sf::FloatRect TileMap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return transform.transformRect(bounds);
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	Set({ 30,30 }, { 50,50 });
	//SetDiamondShape({ 15,15 }, { 100,50 });
	SetOrigin(Origins::TL);
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(textureId);
	SetOrigin(originPreset);
	SetPosition({ 0, 0 });
}

void TileMap::Update(float dt)
{
	UpdateTransform();
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2i& size)
{
	cellCount = count;
	cellSize = size;
	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f texCoord[4] = { {0.f,0.f}, {50.f, 0.f}, {50.f,50.f}, {0.f, 50.f} };
	sf::Vector2f posOffset[4] = { {0.f,0.f}, {(float)size.x, 0.f},{(float)size.x, (float)size.y},{0.f, (float)size.y} };

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex;
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			else
			{
				texIndex = Utils::RandomRange(0, 2);
			}

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j * size.x, i * size.y);
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoord[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::SetDiamondShape(const sf::Vector2i& count, const sf::Vector2i& size)
{
	cellCount = count;
	cellSize = size;
	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f texCoord[4] = { {0.f,0.f}, {50.f, 0.f}, {50.f,50.f}, {0.f, 50.f} };
	sf::Vector2f posOffset[4] = { {0.f,(float)size.y * 0.5f}, {(float)size.x * 0.5f, 0.f},{(float)size.x, (float)size.y * 0.5f},{(float)size.x * 0.5f, (float)size.y} };

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex;
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			else
			{
				texIndex = Utils::RandomRange(0, 2);
			}

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j * size.x, i * size.y*0.5f);
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				if (i % 2)va[vertexIndex].position.x += size.x * 0.5f;
				va[vertexIndex].texCoords = texCoord[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}
