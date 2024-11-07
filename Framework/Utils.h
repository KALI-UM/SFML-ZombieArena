#pragma once

class Utils
{
private:
	static std::mt19937 generator;
	static const float PI;

public:
	static void Init();

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static float RandomValue();	// 0.0f ~ 1.0f
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static sf::Color RandomColor(bool randomOpacity = false);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable &obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f GetOriginValue(Origins preset, const sf::FloatRect bound);

	// Math
	static float Clamp(float value, float min, float max);
	static float Clamp01(float value);
	static float Lerp(float startv, float endv, float ratio, bool clamp=true);
	static sf::Color Lerp(const sf::Color& min, const sf::Color& max, float ratio, bool clamp = true);
	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float ratio, bool clamp = true);
	
	static sf::Vector2f SLerp(const sf::Vector2f& startv, const sf::Vector2f& endv, float radius, float ratio);


	static float Magnitude(const sf::Vector2f& value);
	static float SqrMagnitude(const sf::Vector2f& value);
	static sf::Vector2f GetNomalize(const sf::Vector2f value);
	static void Nomalize(sf::Vector2f& value);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);
	static float AngleRadian(const sf::Vector2f& vec);
	static float Angle(const sf::Vector2f& vec);
	static float Dot(const sf::Vector2f& p1, const sf::Vector2f& p2);

	// Ãæµ¹
	static bool CheckCollision(const sf::FloatRect& rectA, const sf::Transform& transA,
		const sf::FloatRect& rectB, const sf::Transform& transB);
	static bool CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB);
	static bool CheckCollision(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
	static std::vector<sf::Vector2f> GetRectPoints(const sf::FloatRect& rect);
	static std::vector<sf::Vector2f> GetShapePoints(const sf::RectangleShape& shape);
	static std::vector<sf::Vector2f> GetSpritePoints(const sf::Sprite& sprite);
	static std::vector<sf::Vector2f> GetRectanglePointsFromBounds(const sf::FloatRect& localBounds);
	static bool PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA,
		const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB);

	static bool PointInTransformBounds(const sf::Transformable& transformable, 
		const sf::FloatRect& localBounds, const sf::Vector2f point);

};

