#pragma once
#include "Entity.h"

class Egg;

class Block final :public Entity
{
public:
	enum class BlockType
	{
		EggBlock,
		TextBlock
	};

	Block(Point2f position,BlockType blockType);
	~Block() override = default;
	void Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void BlockHit(std::vector <Egg*>& eggs);
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	bool GetIsBlockHit();
	void Reset() override;
private:
	BlockType m_BlockType;
	bool m_IsHit{false};
	float m_HitTimer{ 0 };
};

