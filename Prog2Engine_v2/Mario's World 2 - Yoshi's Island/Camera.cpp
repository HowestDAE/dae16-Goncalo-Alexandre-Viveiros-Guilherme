#include "pch.h"
#include "Camera.h"
#include "Texture.h"


Camera::Camera(Texture* lvlTxt):
	m_LvlTxt{lvlTxt}
{

}

Camera::~Camera()
{
	delete m_LvlTxt;
}

Point2f Camera::Pan(Point2f CamPos, Point2f YoshiPos)
{
	if (YoshiPos.x > 500)
	{
		
	}

	return CamPos;
}