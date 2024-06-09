#pragma once
#include <vector>

class Yoshi;
class Texture;
class Camera
{
public:
	Camera(Point2f camPos, Point2f yoshiStartPos);
	~Camera() = default;
	Camera(const Camera& rhs) = delete;
	Camera& operator=(const Camera& rhs) = delete;
	Camera(Camera&& rhs) = delete;

	void Pan(Yoshi*& yoshiPlyr, float levelStart, float levelEnd);
	void CenterCamera(Point2f yoshiPos);
	Point2f GetCamPos() const;

private:
	Point2f m_CamPosition;

};

