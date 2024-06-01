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

	void Draw() const;
	void Update(float elapsedSec, Point2f yoshiPos);
	std::vector<std::vector<Point2f>> GetPlatformVertices();
	float GetAngle() const;
	Point2f GetPlatformPosition() const;
	Point2f GetCenterPosition() const;
	int GetWhichPlatformIsYoshiOn() const;
	float GetPlatformHeight() const;
	float GetRadius() const;


private:
	Point2f m_Position;
	float m_TxtWidth;
	float m_TxtHeight;
	float m_PlatformWidth;
	float m_PlatformHeight;
	Texture* m_PlatformTxt;
	float m_Radius;
	float m_Angle{0};
	int m_WhichPlatformIsYoshiOn {0};
	std::vector<Point2f> m_PlatformPos {4};

	std::vector< std::vector<Point2f>> m_PlatformVertices{4};



};

