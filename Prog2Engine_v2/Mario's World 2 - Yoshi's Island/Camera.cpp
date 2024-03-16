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

void Camera::Pan(int lvlStartWidth, int lvlStartHeight, int YoshiPos)
{
	
}