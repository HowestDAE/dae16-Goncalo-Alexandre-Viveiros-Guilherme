#pragma once
#include <vector>
class Texture;

class Platforms
{
public:
	Platforms(Point2f position,float txtWidth,float txtHeight,float platformWidth, float platformHeight, const std::string& texturePath,float radius);
	~Platforms();
	Platforms(const Platforms& rhs) = delete;
	Platforms& operator=(const Platforms& rhs) = delete;
	Platforms(Platforms&& rhs) = delete;
	Platforms& operator=(Platforms&& rhs) = delete;

	void Draw() const;
	void Update(float elapsedSec, Point2f yoshiPos, Point2f yoshiVelocity);
	std::vector<std::vector<Point2f>> GetPlatformVertices();
	float GetAngle() const;
	Point2f GetPlatformPosition() const;
	Point2f GetCenterPosition() const;
	int GetWhichPlatformIsYoshiOn() const;
	float GetPlatformHeight() const;
	float GetPlatformWidth() const;
	float GetRadius() const;
	float GetYoshiXPosDifference() const;


private:
	Point2f m_Position;
	float m_TxtWidth;
	float m_TxtHeight;
	float m_PlatformWidth;
	float m_PlatformHeight;
	Texture* m_PlatformTxt;
	float m_Radius;
	float m_Angle{0};
	float m_YoshiXPosDifference{ 0 };
	int m_WhichPlatformIsYoshiOn {0};
	bool m_HasYoshiMovedRecently{false};
	bool m_CalculateNewYoshiPos{ true };
	std::vector<Point2f> m_PlatformPos {4};

	std::vector< std::vector<Point2f>> m_PlatformVertices{4};



};

