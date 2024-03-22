#pragma once

class Texture;
class Camera
{
public:
	Camera(Texture* lvlTxt);
	~Camera();

	Point2f Pan(Point2f CamPos,Point2f YoshiPos);

private:
	Texture* m_LvlTxt;
};

