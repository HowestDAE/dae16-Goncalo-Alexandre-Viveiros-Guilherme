#pragma once

class Texture;
class Camera
{
public:
	Camera(Point2f camPos, Point2f yoshiStartPos);
	~Camera();

	void Pan(Point2f yoshiPos, bool isGrounded, bool isFacingRight);
	Point2f GetCamPos() const;

private:
	Point2f m_CamPosition;
};

