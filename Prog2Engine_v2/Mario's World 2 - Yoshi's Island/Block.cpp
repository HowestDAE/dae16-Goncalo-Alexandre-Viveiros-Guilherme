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

	m_EggTimer += elapsedSec;

	if (m_IsHit == true)
	{
		m_HitTimer += elapsedSec;


		m_VelocityY = 1000;

		if(m_HitTimer > 0.08)
		{
			m_VelocityY = -1000;

			if (m_HitTimer > 0.16)
			{
				m_VelocityY = 0;

				if (m_HitTimer > 0.3)
				{
					m_Position = m_ResetPosition;
					m_IsHit = false;
					m_HitTimer = 0;
				}

				if (m_EggTimer > 2)
				{
					m_EggTimer = 0;
				}
				
			}
		}
	}
}

void Block::BlockHit(std::vector <Egg*>& eggs) 
{
	if (m_BlockType == BlockType::EggBlock)
	{
		m_IsHit = true;
		if (m_EggTimer > 1.5)
		{
			eggs.push_back(new Egg(m_Position));
			eggs.back()->DropEgg();
			eggs.back()->AddVelocity(-210, 40);
		}

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

	m_IsHit     = false;
	m_HitTimer = 0;
	m_EggTimer = 0;
}
