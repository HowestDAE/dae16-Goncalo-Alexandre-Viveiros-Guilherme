#pragma once
#include "Entity.h"

class Yoshi;
class Mario: public Entity
{
public:
	Mario(Yoshi* PlyrYoshi);
	~Mario();
	void Draw();
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);

private:
	Yoshi* m_Yoshi;
	float m_XTxtPos2;
	float m_YTxtPos2;
	float m_TxtWidth2;
	float m_TxtHeight2;
	float m_Time;
};

