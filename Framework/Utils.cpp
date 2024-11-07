#include "stdafx.h"
#include "Utils.h"
#include <cmath>

std::mt19937 Utils::generator;
const float Utils::PI = acosf(-1.f);

void Utils::Init()
{
	std::random_device rd;
	generator.seed(rd());
}

int Utils::RandomRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(generator);
}

float Utils::RandomRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(generator);
}

float Utils::RandomValue()
{
	return RandomRange(0.f, 1.f);
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	float angle = RandomRange(0.f, 2.f * PI);
	return sf::Vector2f(std::cosf(angle), std::sinf(angle));
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

sf::Color Utils::RandomColor(bool randomOpacity)
{
	return sf::Color(RandomRange(0, 255), RandomRange(0, 255), RandomRange(0, 255), randomOpacity ? RandomRange(0, 255) : 255);
}

float Utils::Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float Utils::Clamp01(float value)
{
	return Clamp(value, 0, 1);
}

float Utils::Lerp(float startv, float endv, float ratio, bool clamp)
{
	if (clamp)ratio = Clamp01(ratio);
	return startv * (1.f - ratio) + endv * ratio;
}

sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float ratio, bool clamp)
{
	if (clamp)ratio = Clamp01(ratio);
	return sf::Color(Lerp(min.r, max.r, ratio), Lerp(min.g, max.g, ratio), Lerp(min.b, max.b, ratio), Lerp(min.a, max.a, ratio));
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float ratio, bool clamp)
{
	if (clamp)ratio = Clamp01(ratio);
	return sf::Vector2f(Lerp(min.x, max.x, ratio), Lerp(min.y, max.y, ratio));
}

sf::Vector2f Utils::SLerp(const sf::Vector2f& startv, const sf::Vector2f& endv, float radius, float ratio)
{
	float theta = atan2f(startv.y, startv.x) - atan2f(endv.y, endv.x);
	return sf::Vector2f(radius * cosf(Lerp(0, theta, ratio)), radius * sinf(Lerp(0, theta, ratio)));
}


float Utils::Magnitude(const sf::Vector2f& value)
{
	return sqrtf(SqrMagnitude(value));
}

float Utils::SqrMagnitude(const sf::Vector2f& value)
{
	return value.x * value.x + value.y * value.y;
}

sf::Vector2f Utils::GetNomalize(const sf::Vector2f value)
{
	float magnitude = Magnitude(value);
	if (magnitude != 0)
		return value / magnitude;
	return value;
}

void Utils::Nomalize(sf::Vector2f& value)
{
	float magnitude = Magnitude(value);
	if (magnitude != 0)
		value /= magnitude;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p1 - p2);
}

float Utils::RadianToDegree(float radian)
{
	return radian * (180.f / PI);
}

float Utils::DegreeToRadian(float degree)
{
	return degree * (PI / 180.f);
}

float Utils::AngleRadian(const sf::Vector2f& vec)
{
	return std::atan2(vec.y, vec.x);
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(AngleRadian(vec));
}

float Utils::Dot(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect rect)
{
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;
	obj.setOrigin(newOrigin);
	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::GetOriginValue(Origins preset, const sf::FloatRect bound)
{
	sf::Vector2f newOrigin(bound.width, bound.height);
	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;
	return newOrigin;
}


bool Utils::CheckCollision(const sf::FloatRect& rectA, const sf::Transform& transA, const sf::FloatRect& rectB, const sf::Transform& transB)
{
    auto pointsA = GetRectanglePointsFromBounds(rectA);
    auto pointsB = GetRectanglePointsFromBounds(rectB);
    return PolygonsIntersect(pointsA, transA, pointsB, transB);
}

bool Utils::CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB)
{
    auto pointsA = GetShapePoints(shapeA);
    auto pointsB = GetShapePoints(shapeB);
    return PolygonsIntersect(pointsA, shapeA.getTransform(), pointsB, shapeB.getTransform());
}

bool Utils::CheckCollision(const sf::Sprite& spriteA, const sf::Sprite& spriteB)
{
    auto pointsA = GetSpritePoints(spriteA);
    auto pointsB = GetSpritePoints(spriteB);
    return PolygonsIntersect(pointsA, spriteA.getTransform(), pointsB, spriteB.getTransform());
}

std::vector<sf::Vector2f> Utils::GetRectPoints(const sf::FloatRect& rect)
{
    return std::vector<sf::Vector2f>();
}

std::vector<sf::Vector2f> Utils::GetShapePoints(const sf::RectangleShape& shape)
{
    sf::FloatRect localBounds = shape.getLocalBounds();
    return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetSpritePoints(const sf::Sprite& sprite)
{
    sf::FloatRect localBounds = sprite.getLocalBounds();
    return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetRectanglePointsFromBounds(const sf::FloatRect& localBounds)
{
    std::vector<sf::Vector2f> points(4);
    points[0] = sf::Vector2f(localBounds.left, localBounds.top);
    points[1] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top);
    points[2] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top + localBounds.height);
    points[3] = sf::Vector2f(localBounds.left, localBounds.top + localBounds.height);
    return points;
}

bool Utils::PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA, const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB)
{
    std::vector<sf::Vector2f> axes;
    int countA = polygonA.size();
    for (int i = 0; i < countA; ++i)
    {
        sf::Vector2f p1 = transformA.transformPoint(polygonA[i]);
        sf::Vector2f p2 = transformA.transformPoint(polygonA[(i + 1) % countA]);
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        axes.push_back(Utils::GetNomalize(normal));
    }

    int countB = polygonB.size();
    for (int i = 0; i < countB; ++i)
    {
        sf::Vector2f p1 = transformB.transformPoint(polygonB[i]);
        sf::Vector2f p2 = transformB.transformPoint(polygonB[(i + 1) % countB]);
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        axes.push_back(Utils::GetNomalize(normal));
    }

    for (const auto& axis : axes)
    {
        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::lowest();
        for (const auto& point : polygonA)
        {
            sf::Vector2f transformedPoint = transformA.transformPoint(point);
            float projection = Dot(axis, transformedPoint);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::lowest();
        for (const auto& point : polygonB)
        {
            sf::Vector2f transformedPoint = transformB.transformPoint(point);
            float projection = Dot(axis, transformedPoint);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        if (maxA < minB || maxB < minA)
        {
            return false;
        }
    }
    return true;
}

bool Utils::PointInTransformBounds(const sf::Transformable& transformable, const sf::FloatRect& localBounds, const sf::Vector2f point)
{
    sf::Transform inverse = transformable.getInverseTransform();
    sf::Vector2f localPoint = inverse.transformPoint(point);
    return localBounds.contains(localPoint);
}
