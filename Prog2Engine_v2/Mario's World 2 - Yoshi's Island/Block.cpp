#include "pch.h"
#include "Block.h"

#include "Egg.h"

Block::Block(Point2f position, BlockType blockType): Entity("GeneralSprites.png",16,16,position),
m_BlockType(blockType)
{
}


void Block::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);

	if (m_IsHit == true)
	{
		m_HitTimer += elapsedSec;

		m_VelocityY = 1000;

		if(m_HitTimer > 0.08)
		{
			m_VelocityY = -975;

			if (m_HitTimer > 0.16)
			{
				m_VelocityY = 0;

				if (m_HitTimer > 0.6)
				{
					m_HitTimer = 0;
					m_IsHit = false;
				}
				
			}
		}
	}
}

void Block::BlockHit(std::vector <Egg*>& eggs) 
{
	if (m_BlockType == BlockType::EggBlock)
	{
		eggs.push_back(new Egg(m_Position));
		eggs.back()->DropEgg();
		eggs.back()->AddVelocity(-70, 200);

		m_IsHit = true;
	}
	else
	{
		
	}

}

void Block::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	
}

void Block::Animate(float elapsedSec)
{
	if (m_BlockType == BlockType::EggBlock)
	{
		m_YTxtPos = 66;
		m_XTxtPos = 232;
	}
	else
	{
		m_YTxtPos = 86;

		if (m_IsHit == false)
		{
			m_XTxtPos = 226;
		}
		else
		{
			m_XTxtPos = 243;
		}
	}
}

bool Block::GetIsBlockHit()
{
	return m_IsHit;
}

void Block::Reset()
{
	Entity::Reset();

	bool m_IsHit     = false;
	float m_HitTimer = 0;
}
