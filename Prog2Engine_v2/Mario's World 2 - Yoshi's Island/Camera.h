#pragma once

class Texture;
class Camera
{
public:
	Camera(Point2f CamPos, Point2f YoshiStartPos);
	~Camera();

	void Pan(Point2f YoshiPos, bool isGrounded, bool isFacingRight);
	Point2f GetCamPos();

private:
	Point2f m_CamPosition;
};

