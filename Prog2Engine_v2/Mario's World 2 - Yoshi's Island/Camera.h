#pragma once

class Texture;
class Camera
{
public:
	Camera(Point2f CamPos, Point2f YoshiStartPos);
	~Camera();

	Point2f Pan(Point2f YoshiPos) ;

private:
	Point2f m_YoshiPosition;
	Point2f m_CamPosition;

	float lastYoshiXPos;
	float lastYoshiYPos;
};

