#pragma once
#include "Entity.h"

class SoundManager;

class Coin:public Entity
{
public:
	explicit Coin(bool isRedCoin,Point2f position);
	~Coin() override;
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	void Sound(SoundManager* soundManager);
	bool GetIsRedCoin();
	void FlipIsActive(SoundManager* soundManager);

private:
	bool m_IsRedCoin;

};

