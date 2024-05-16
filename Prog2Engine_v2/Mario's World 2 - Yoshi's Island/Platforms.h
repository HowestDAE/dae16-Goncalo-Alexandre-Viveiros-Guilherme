#pragma once
#include <vector>
class Texture;

class Platforms
{
public:
	Platforms(Point2f position,float txtWidth,float txtHeight,float platformWidth, float platformHeight, const std::string& texturePath,float radius);
	~Platforms();
	void Draw() const;
	void Update();
	std::vector<std::vector<Point2f>> GetPlatformVertices();

private:
	Point2f m_Position;
	float m_TxtWidth;
	float m_TxtHeight;
	float m_PlatformWidth;
	float m_PlatformHeight;
	Texture* m_PlatformTxt;
	float m_Radius;
	float m_Angle{0};
	Point2f m_PlatformPos1;
	Point2f m_PlatformPos2;
	Point2f m_PlatformPos3;
	Point2f m_PlatformPos4;

	std::vector< std::vector<Point2f>> m_PlatformVertices{4};
	std::vector<Point2f> m_Platform1Vertices{ 2 };
	std::vector<Point2f> m_Platform2Vertices{ 2 };
	std::vector<Point2f> m_Platform3Vertices{ 2 };
	std::vector<Point2f> m_Platform4Vertices{ 2 };

};

