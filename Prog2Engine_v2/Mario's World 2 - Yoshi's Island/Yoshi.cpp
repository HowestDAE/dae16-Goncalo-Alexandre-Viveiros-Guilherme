#include "pch.h"
#include "Yoshi.h"
#include <iostream>
#include "Enemy.h"
#include "Texture.h"
#include "utils.h"
#include "Egg.h"

Yoshi::Yoshi(Point2f startPos):
Entity("Yoshi_SpriteSheet.png",32,30,startPos),
	m_IsMarioOn{ true },
	m_MarioTimer{ 10 }
{
	
}

Yoshi::~Yoshi()
{

}

void Yoshi::Draw() const
{
	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		m_Eggs[idx]->Draw();
	}

	Entity::Draw();

	if (m_IsTonguing == true)
	{
		
		m_EntityTxt->Draw(m_TongueHitBox,Rectf(41, 962, 8, 3));

		if (m_IsFacingRight == true)
		{
			m_EntityTxt->Draw(Rectf{ m_TongueHitBox.left + m_TongueHitBox.width,m_TongueHitBox.bottom,8,7 }, Rectf{ 32 ,964,8,7 });
			

		}
		else
		{
			m_EntityTxt->Draw(Rectf{ m_TongueHitBox.left ,m_TongueHitBox.bottom,8,7 }, Rectf{ 32 ,964,8,7 });
		}
	}


}

void Yoshi::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);

	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		m_Eggs[idx]->Update(m_Position,m_Eggs.size(),platforms,elapsedSec);
	}

	float topHeight;
	float startHeight{m_Position.y};

	if (m_IsGrounded == true)
	{
		m_FlightTime = 0;
		
		if (m_IsYoshiJumping == true)
		{
			m_Position.y += 20;
			m_VelocityY = 900;
		}
	
	}

	else 
	{
		if (m_IsYoshiJumping == true)
		{
			if (m_VelocityY < 0)
			{
				topHeight = m_Position.y;
				m_FlightTime += elapsedSec;
				if (m_FlightTime < 1)
				{
					currentState = AnimState::Hovering;
					m_VelocityY = 30;
				}

			}

			
		}

	}


	if (m_IsTonguing == true)
	{
		if (m_IsFacingRight == true)
		{
			m_TongueHitBox = Rectf(m_Position.x + m_TxtWidth * 2, m_Position.y + m_TxtHeight, 100, 5);
		}

		else
		{
			m_TongueHitBox = Rectf(m_Position.x - 100, m_Position.y + m_TxtHeight, 100, 5);
		}
	}

	else if (m_IsTonguing == false)
	{
		m_TongueHitBox = Rectf(-1000, 0, 0, 0);
	}

}


void Yoshi::Animate(float elapsedSec)
{

	////////////////////////////////////
	// CHECK CURRENT ANIMATION STATE //
	//////////////////////////////////

	if (m_VelocityX == 0 && m_VelocityY == 0)
	{
		currentState = AnimState::Idle;

	}

	if (m_VelocityX > 0 && m_VelocityX < 260 && m_VelocityY == 0 || m_VelocityX < 0 && m_VelocityX > -260 && m_VelocityY == 0)
	{
		currentState = AnimState::Walking;
	}

	if (m_VelocityX > 260 && m_VelocityY == 0 || m_VelocityX < -260 && m_VelocityY == 0)
	{
		currentState = AnimState::Sprinting;
	}

	if (m_IsTonguing == true)
	{
		currentState = AnimState::Tongue;
	}

	if (m_IsMouthFull)
	{
		if (m_VelocityX == 0)
		{
			currentState = AnimState::FullIdle;

		}

		if (m_VelocityX > 0 && m_VelocityX < 260 || m_VelocityX < 0 && m_VelocityX > -260)
		{
			currentState = AnimState::FullWalking;
		}

		if (m_VelocityX > 260 || m_VelocityX < -260)
		{
			currentState = AnimState::FullSprinting;
		}
	}

	////////////////////////////////////
	// ANIMATIONS FOR CURRENT STATE  //
	//////////////////////////////////


	//Animations for Idle State
	if (currentState == AnimState::Idle)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 29;
		}

		m_TxtWidth = 27;
		m_TxtHeight = 32;
		m_YTxtPos = 483;
		m_FrameTime += elapsedSec;


		if (m_FrameTime >= 0.13)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos >= 29 + m_TxtWidth * 7)
		{
			m_XTxtPos = 29;
		}

		if (m_XTxtPos < 29)
		{
			m_XTxtPos = 29;
		}

		lastState = AnimState::Idle;
	}

	//Animate for Walking state
	if (currentState == AnimState::Walking)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 2;
		}

		m_TxtWidth = 27;
		m_TxtHeight = 32;
		m_YTxtPos = 450;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos >= 2 + m_TxtWidth * 10)
		{
			m_XTxtPos = 2;
		}

		if (m_XTxtPos < 2)
		{
			m_XTxtPos = 2;
		}

		lastState = AnimState::Walking;
	}

	//Animate for Sprinting State
	if (currentState == AnimState::Sprinting)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 2;
		}
		//m_CurrentTxtWidth = m_StdTxtWidth + 6;
		m_TxtWidth = 36;
		m_TxtHeight = 26;
		m_YTxtPos = 703;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			m_XTxtPos += m_TxtWidth + 2;
			m_FrameTime = 0;

		}

		if (m_XTxtPos >= m_TxtWidth * 2 + 2)
		{
			m_XTxtPos = 2;
		}

		lastState = AnimState::Sprinting;
	}

	//Animate for Tonguing State
	if (currentState == AnimState::Tongue)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 2;
			m_FrameTime = 0;
		}

		m_TxtWidth = 30;
		m_TxtHeight = 25;
		m_YTxtPos = 978;
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.4)
		{
			m_IsTonguing = false;
		}

		lastState = currentState;
	}

	if (currentState == AnimState::Jumping)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 2;
		}

		m_YTxtPos = 622;
		m_TxtWidth = 25;
		m_TxtHeight = 33;

		if (m_VelocityY < 0)
		{
			m_XTxtPos = 2 + m_TxtWidth;
		}

		if (m_XTxtPos > 2 + m_TxtWidth * 3)
		{
			m_XTxtPos = 2;
		}

		lastState = currentState;
	}

	if (currentState == AnimState::Hovering)
	{
		if (lastState != currentState)
		{
			
			m_XTxtPos = 2;
			m_FrameTime = 0;
		}

		m_TxtWidth = 25;
		m_TxtHeight = 34;
		m_YTxtPos = 770;
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.05)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos > 2 + m_TxtWidth * 2)
		{
			m_XTxtPos = 2;
		}

		lastState = currentState;
	}

	if (currentState == AnimState::FullIdle)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 720;
		}

		m_TxtWidth = 29;
		m_TxtHeight = 34;
		m_YTxtPos = 456;
		m_FrameTime += elapsedSec;


		if (m_FrameTime >= 0.13)
		{

			m_XTxtPos += m_TxtWidth ;
			m_FrameTime = 0;

		}

		if (m_XTxtPos >= 720 + m_TxtWidth * 7)
		{
			m_XTxtPos = 720;
		}

		if (m_XTxtPos < 720)
		{
			m_XTxtPos = 720;
		}

		lastState = AnimState::FullIdle;
	}

	//Animate for Walking state
	if (currentState == AnimState::FullWalking)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 720;
		}

		m_TxtWidth = 28;
		m_TxtHeight = 32;
		m_YTxtPos = 421;
		m_FrameTime += elapsedSec;


		if (m_FrameTime >= 0.02)
		{
			m_XTxtPos += m_TxtWidth + 1;
			m_FrameTime = 0;
		}

		if (m_XTxtPos >= 720 + m_TxtWidth * 10 + 9)
		{
			m_XTxtPos = 720;
		}

		if (m_XTxtPos < 720)
		{
			m_XTxtPos = 720;
		}

		lastState = AnimState::FullWalking;
	}

	//Animate for Sprinting State
	if (currentState == AnimState::FullSprinting)
	{
		if (lastState != currentState)
		{
			m_XTxtPos = 723;
		}
		//m_CurrentTxtWidth = m_StdTxtWidth + 6;
		m_TxtWidth = 37;
		m_TxtHeight = 28;
		m_YTxtPos = 663;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			m_XTxtPos += m_TxtWidth + 2;
			m_FrameTime = 0;
		}

		if (m_XTxtPos >= 723 + m_TxtWidth * 2 + 2)
		{
			m_XTxtPos = 723;
		}

		lastState = AnimState::Sprinting;
	}

	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		m_Eggs[idx]->Animate(elapsedSec);
	}
}



void Yoshi::KeysDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		if (m_VelocityX > -310)
		{
			m_VelocityX -= 33;
		}

		break;
	case SDLK_RIGHT:
		if (m_VelocityX < 310)
		{
			m_VelocityX += 33;
		}
		break;
	case SDLK_z:
		m_IsYoshiJumping = true;
		currentState = AnimState::Jumping;
		break;
	case SDLK_DOWN:
		if (m_IsMouthFull == true)
		{
			m_Eggs.push_back(new Egg(m_Position));

			m_IsMouthFull = false;
		}
		break;
	case SDLK_UP:

		m_IsLookingUp = true;

		break;

	case SDLK_x:

		m_IsTonguing = true;
		
		break;
	case SDLK_c:
		if (m_Eggs.size() > 0)
		{
			//TODO add throwing of the egg
			m_Eggs.pop_back();
		}
		break;
	}


}

void Yoshi::KeysUp(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:

		break;
	case SDLK_RIGHT:

		break;
	case SDLK_z:
		m_IsYoshiJumping = false;
		break;
	case SDLK_DOWN:

		break;
	case SDLK_UP:

		m_IsLookingUp = false;

		break;

	case SDLK_x:

		m_IsTonguing = false;

		break;
	case SDLK_c:

		break;

	}
}


void Yoshi::Debug()
{

	
}

bool Yoshi::GetIsMarioOn() const
{
	return m_IsMarioOn;
}


void Yoshi::HitCheck(std::vector<Enemy*>& Enemies)
{
	if (Enemies.size() > 0)
	{
		for (int idx{ 0 }; idx < Enemies.size(); idx++)
		{
			if (Enemies[idx] != nullptr)
			{
				if (utils::IsOverlapping(m_Hitbox, Enemies[idx]->GetHitBox()) == true)
				{
					if (Enemies[idx]->GetIsSquashable() == true)
					{
						if (m_Hitbox.bottom > Enemies[idx]->GetHitBox().bottom + (m_TxtHeight / 3))
						{
							Enemies[idx]->EnemyDeath();
							Enemies[idx] = nullptr;
							m_VelocityY *= -1;
						}
						else
						{
							m_IsMarioOn = false;
						}

					}
				}
			}
			if (Enemies[idx] != nullptr)
			{
				if (Enemies[idx]->GetIsEdible() == true)
				{
					if (utils::IsOverlapping(m_TongueHitBox, Enemies[idx]->GetHitBox()) == true)
					{
						Enemies[idx]->EnemyDeath();
						Enemies[idx] = nullptr;
						m_IsMouthFull = true;
					}
				}
			}
			
		}
	}
	
	
}

