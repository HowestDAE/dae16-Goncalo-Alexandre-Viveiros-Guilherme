#pragma once
#include "Entity.h"

class Yoshi;
class Mario: public Entity
{
public:
	Mario(Yoshi* PlyrYoshi);
	~Mario();
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);

private:
	Yoshi* m_Yoshi;

};

