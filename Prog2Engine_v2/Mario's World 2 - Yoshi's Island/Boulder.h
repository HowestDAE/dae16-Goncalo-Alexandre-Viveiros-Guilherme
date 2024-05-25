#pragma once
#include "Entity.h"

class Enemy;

class Boulder final:public Entity
{
public:
	explicit Boulder(Point2f startPos);
	~Boulder() override = default;
	void Hitcheck(const std::vector<Enemy*>& enemies) const;
	void AddVelocity(bool isYoshiFacingRight);

};

