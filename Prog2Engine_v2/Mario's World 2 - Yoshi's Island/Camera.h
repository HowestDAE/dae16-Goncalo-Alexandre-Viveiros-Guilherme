#pragma once

class Texture;
class Camera
{
public:
	Camera(Texture* lvlTxt);
	~Camera();

	void Pan(int lvlStartWidth,int lvlStartHeight,int YoshiPos);

private:
	Texture* m_LvlTxt;
};

