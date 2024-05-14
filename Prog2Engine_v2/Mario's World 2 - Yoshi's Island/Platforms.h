#pragma once
class Texture;

class Platforms
{
public:
	Platforms(Point2f position,float txtWidth,float txtHeight,float platformWidth, float platformHeight, const std::string& texturePath);
	~Platforms();
	void Draw() const;
	void Update();

private:
	Point2f m_Position;
	float m_TxtWidth;
	float m_TxtHeight;
	float m_PlatformWidth;
	float m_PlatformHeight;
	Texture* m_PlatformTxt;
	float m_Radius;
	float m_Angle;
	Point2f m_PlatformPos1;
	Point2f m_PlatformPos2;
	Point2f m_PlatformPos3;
	Point2f m_PlatformPos4;
};

