#pragma once
#include "Entity.h"

class Coin:public Entity
{
public:
	explicit Coin(bool isRedCoin,Point2f position);
	~Coin() override;
	void Update();
	void Animate(float elapsedSec) override;
	bool GetIsRedCoin();

private:
	bool m_IsRedCoin;


};

