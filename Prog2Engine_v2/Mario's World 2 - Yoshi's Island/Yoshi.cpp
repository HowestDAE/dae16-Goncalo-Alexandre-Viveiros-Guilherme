#include "pch.h"
#include "Yoshi.h"
#include <iostream>

#include "Block.h"
#include "Enemy.h"
#include "Texture.h"
#include "utils.h"
#include "Egg.h"
#include "WingedClouds.h"
#include "Flowers.h"
#include "Boulder.h"
#include "Coin.h"
#include "SoundManager.h"
#include "Star.h"

Yoshi::Yoshi(Point2f startPos):
Entity("Yoshi_SpriteSheet.png",32,30,startPos),
	m_IsMarioOn{ true },
	m_MarioTimer{ 10 },
	m_Tongue{startPos,8}
{
	
}

Yoshi::~Yoshi()
{
	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		delete m_Eggs[idx];
	}
}

void Yoshi::Draw() const
{
	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		m_Eggs[idx]->Draw();
	}

	if (m_IsHit == true)
	{
		if (m_HitTimer > 0.05)
		{
			Entity::Draw();
		}
	}

	else
	{
		Entity::Draw();
	}
	
	
#pragma region Debug
	//utils::SetColor(Color4f{ 1,0,0,1 });
	//////left side
	//utils::DrawLine(Point2f{ m_FeetPos.x - 13,m_FeetPos.y +32 },
	//	Point2f{ m_FeetPos.x - 13,m_FeetPos.y });			 
	//utils::DrawLine(Point2f{ m_FeetPos.x + 13,m_FeetPos.y +32 },
	//	Point2f{ m_FeetPos.x + 13,m_FeetPos.y });

	utils::SetColor(Color4f{ 0,1,0,1 });
	//if (m_IsFacingRight == true)
	//{
	//	utils::DrawLine(Point2f{ m_FeetPos.x,m_Position.y + 32 },
	//		Point2f{ m_FeetPos.x + 15,m_Position.y + 32 });
	///*	utils::DrawLine(Point2f{ m_FeetPos.x,m_Position.y + 32 },
	//		Point2f{ m_FeetPos.x - 15,m_Position.y + 32 });*/
	//	
	//}
	//else
	//{
	//	utils::DrawLine(Point2f{ m_FeetPos.x,m_Position.y + 32},
	//		Point2f{ m_FeetPos.x + 15,m_Position.y + 32 });
	//	utils::DrawLine(Point2f{ m_FeetPos.x,m_Position.y + 32 },
	//		Point2f{ m_FeetPos.x - 15,m_Position.y + 32 });
	//}

	//utils::DrawPoint(Point2f(m_FeetPos.x,m_Position.y), 2);
#pragma endregion


	if (m_IsTonguing == true)
	{
		if (m_IsFacingRight == true)
		{
			m_EntityTxt->Draw(Rectf(m_Position.x + m_TxtWidth * 2, m_Position.y + m_TxtHeight, 350 * m_FrameTime, 5), Rectf(41, 962, 8, 3));
			m_EntityTxt->Draw(Rectf{ m_Tongue.center.x,m_Tongue.center.y,8,7 }, Rectf{ 32 ,964,8,7 });
		}
		else
		{
			m_EntityTxt->Draw(Rectf(m_Tongue.center.x, m_Position.y + m_TxtHeight, 330*m_FrameTime, 5), Rectf(41, 962, 8, 3));
			m_EntityTxt->Draw(Rectf{ m_Tongue.center.x,m_Tongue.center.y,8,7 }, Rectf{ 32 ,964,8,7 });
		}
	}

}

void Yoshi::Update(const std::vector<std::vector<Point2f>>& platforms, const std::vector< std::vector<Point2f>>& movingPlatforms, SoundManager*& soundManager, const float elapsedSec)
{
	//updates Yoshis Feet position
	if (m_IsFacingRight == true)
	{
		m_FeetPos = Point2f{ m_Position.x + 19, m_Position.y - 3 };
	}
	else
	{
		m_FeetPos = Point2f{ m_Position.x + 39,m_Position.y - 3 };
	}

	Collision(platforms, movingPlatforms, elapsedSec);


#pragma region Jump

	if (m_IsYoshiJumping == true)
	{
		if (m_IsGrounded == true)
		{
			m_PlayJumpSFX = true;

			m_IsJumpDone = false;

			m_FlightTime = 0;

			m_JumpTimer = 0;

			m_Position.y += 5;

			m_VelocityY += 15.f;

		}
		else
		{
			m_JumpTimer += elapsedSec;
			if (m_JumpTimer < 0.15)
			{
				m_VelocityY += 15.f;
			}
		}
		if (m_VelocityY < 0)
		{
			m_IsJumpDone = true;
		}

		if (m_IsJumpDone == true)
		{

			m_FlightTime += elapsedSec;

			if (m_FlightTime < 0.8)
			{
				m_CurrentState = AnimState::Hovering;
				m_VelocityY *= -1.f;

				if (m_FlightTime > 0.75)
				{
					m_VelocityY *= -1.f;
					m_VelocityY += 120.f;
				}
			}


		}

	}


	

#pragma endregion

#pragma region Tongue
	if (m_IsTonguing == true)
	{

		m_Tongue.center.y = m_Position.y + m_TxtHeight;

		if (m_IsFacingRight == true)
		{
			m_Tongue.center.x = (m_Position.x + m_TxtWidth*2) + 350 * m_FrameTime;

			if (m_Tongue.center.x > m_Position.x + 150)
			{
				m_IsTonguing = false;
			}
		}

		else
		{
			m_Tongue.center.x = (m_Position.x + 20 )- 350 * m_FrameTime;

			if (m_Tongue.center.x < m_Position.x - 150)
			{
				m_IsTonguing = false;
			}
		}

		
	}

	else if (m_IsTonguing == false)
	{
		m_Tongue.center.x = -3000;
		m_Tongue.center.y = -3000;
	}
#pragma endregion

#pragma region MarioOn
	if (m_IsMarioOn == false)
	{
		m_Countdown += elapsedSec;

		if (m_MarioTimer != 0)
		{
			if (m_Countdown >= 1)
			{
				m_MarioTimer -= 1;
				m_Countdown = 0;
			}
		}
		
	}

	if (m_IsMarioOn == true)
	{
		m_Countdown += elapsedSec;

		if (m_MarioTimer != 10)
		{
			if (m_Countdown >= 1)
			{
				m_MarioTimer += 1;
				m_Countdown = 0;
			}
		}
		
	}
#pragma endregion
	
#pragma region Eggs
	////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		if (m_IsHoldingEgg == true)
		{
			if (m_Eggs[idx] != m_Eggs.back())
			{
				m_Eggs[idx]->Update(m_Position, m_IsFacingRight, idx, platforms, elapsedSec);
			}
		}

		else
		{
			m_Eggs[idx]->Update(m_Position, m_IsFacingRight, idx, platforms, elapsedSec);

		}
		
		if (m_Eggs.back()->GetIsThrown() == true)
		{
			if (m_Eggs.back()->GetPosition().x > m_Position.x + 700 || m_Eggs.back()->GetPosition().x < m_Position.x - 700)
			{
				m_Eggs.pop_back();
			}

			else if (m_Eggs.back()->GetPosition().y > m_Position.y + 700 || m_Eggs.back()->GetPosition().y < m_Position.y - 700)
			{
				m_Eggs.pop_back();
			}

		}

	}

	if (m_IsHoldingEgg == true)
	{
		m_Eggs.back()->HoldEgg(m_Hitbox, m_IsFacingRight,m_IsCalculatingAngle,elapsedSec);
		if (m_IsCrouching == true) { m_IsHoldingEgg = false; }
		if (m_IsTonguing == true) { m_IsHoldingEgg = false; }

	}

#pragma endregion

	//updates Yoshis Feet position
	if (m_IsFacingRight == true)
	{
		m_FeetPos = Point2f{ m_Position.x + 19, m_Position.y - 3 };
	}
	else
	{
		m_FeetPos = Point2f{ m_Position.x + 39,m_Position.y - 3 };
	}

	if (m_IsTongueReady == false)
	{
		m_ControlsTimer += elapsedSec;

		if (m_ControlsTimer > 0.7)
		{
			m_IsTongueReady = true;
			m_ControlsTimer = 0;
		}
	}

	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;

	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;

	//Update Hitbox

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	Animate(elapsedSec);
	Sound(soundManager);
}

void Yoshi::Collision(const std::vector<std::vector<Point2f>>& platforms,const std::vector<std::vector<Point2f>>& movingPlatforms, const float elapsedSec)
{

#pragma region Collision

	utils::HitInfo hit_info;


	if (m_TerminalVlcityTimer > 1)
	{
		m_TerminalVlcityTimer = 1;
	}
	else
	{
		m_TerminalVlcityTimer += elapsedSec;
	}

	//Floor Collisions
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{

		//Checks to see if its a brown platform and if so it changes behavior accordingly
		if (platforms[idx].size() == 2)
		{
			if (m_VelocityY <= 0)
			{
				//checks collision from the left side of Yoshis feet
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x - 13,m_FeetPos.y + 32 },
					Point2f{ m_FeetPos.x - 13,m_FeetPos.y }, hit_info))
				{
					m_VelocityY = 0;
					m_Position.y = hit_info.intersectPoint.y;
					m_IsGrounded = true;
					m_TerminalVlcityTimer = 0;
					break;
				}

				//checks collision from the right side of Yoshis feet
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 13,m_FeetPos.y + 32 },
					Point2f{ m_FeetPos.x + 13,m_FeetPos.y }, hit_info))
				{
					m_VelocityY = 0;
					m_Position.y = hit_info.intersectPoint.y;
					m_IsGrounded = true;
					m_TerminalVlcityTimer = 0;
					break;
				}

				//checks collision from the middle of Yoshis feet
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x ,m_FeetPos.y + 32 },
					Point2f{ m_FeetPos.x ,m_FeetPos.y }, hit_info))
				{
					m_VelocityY = 0;
					m_Position.y = hit_info.intersectPoint.y;
					m_IsGrounded = true;
					m_TerminalVlcityTimer = 0;
					break;
				}

			}

		}
		else
		{
			//floor collision

			//checks collision from the left side of Yoshis feet

			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x - 13,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x - 13,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				break;
			}

			//checks collision from the right side of Yoshis feet
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 13,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x + 13,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				break;
			}

			//checks collision from the middle of Yoshis feet
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x ,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x ,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				break;
			}

			//checks head collision for yoshi
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x ,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x ,m_FeetPos.y + 64 }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y - m_TxtWidth * 2;
				break;
			}
			//Gravity
			if (idx == 0) //to prevent gravity from getting looped 12 times
			{
				m_IsGrounded = false;

				if (m_VelocityY > -480.f)
				{
					m_VelocityY -= 48.f * m_TerminalVlcityTimer;
				}

				if (m_VelocityY < -480.f)
				{
					m_VelocityY += 48.f;
				}

			}

		}


		if (m_IsStandingOnEntity == true)
		{
			m_VelocityY = 0;
			m_Position.y = m_LvlEntityTop;
			m_IsGrounded = true;
			m_TerminalVlcityTimer = 0;

			break;
		}


	}

	//Wall Collision and pushing

	m_PushTimer += elapsedSec;

	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{
		if (platforms[idx].size() != 2)
		{
			if (m_IsFacingRight == true)
			{
				//left side
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 6,m_Position.y + 32 },
					Point2f{ m_FeetPos.x - 15,m_Position.y + 32 }, hit_info))
				{
					m_Position.x = hit_info.intersectPoint.x; //Teleports entity to the point of intersection with a small offset
					break;
				}

				//right side
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 6,m_Position.y + 32 },
					Point2f{ m_FeetPos.x + 15,m_Position.y + 32 }, hit_info))
				{
					m_Position.x = hit_info.intersectPoint.x - m_TxtWidth - 5; //Teleports entity to the point of intersection with a small offset
					if (m_IsGrounded == true)
					{
						m_IsPushing = true;
					}
					m_PushTimer = 0;
					break;
				}

			}

			else
			{
				//right side
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x - 6,m_Position.y + 32 },
					Point2f{ m_FeetPos.x + 15,m_Position.y + 32 }, hit_info))
				{
					m_Position.x = hit_info.intersectPoint.x - 60; //Teleports entity to the point of intersection with a small offset
					break;
				}

				//left side
				if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x - 6,m_Position.y + 32 },
					Point2f{ m_FeetPos.x - 19,m_Position.y + 32 }, hit_info))
				{
					m_Position.x = hit_info.intersectPoint.x - 20; //Teleports entity to the point of intersection with a small offset
					if (m_IsGrounded == true)
					{
						m_IsPushing = true;
					}
					m_PushTimer = 0;
					break;
				}


			}
		}
	}

	//stops pushing after a brief interval
	if (m_PushTimer > 0.03)
	{
		m_IsPushing = false;
	}

#pragma endregion

#pragma region Special Collisions

	//Collisions

	for (int idx{ 0 }; idx < movingPlatforms.size(); idx++)
	{
		//floor collision


		if (m_VelocityY <= 0)
		{

			//checks collision from the middle of Yoshis feet
			if (utils::Raycast(movingPlatforms[idx], Point2f{ m_FeetPos.x ,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x ,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				if (m_VelocityX == 0)
				{
					m_IsOnMovingPlatform = true;
				}
				break;

			}

			//checks collision from the left side of Yoshis feet
			if (utils::Raycast(movingPlatforms[idx], Point2f{ m_FeetPos.x - 13,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x - 13,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				if (m_VelocityX == 0)
				{
					m_IsOnMovingPlatform = true;
				}

				break;

			}

			//checks collision from the right side of Yoshis feet
			if (utils::Raycast(movingPlatforms[idx], Point2f{ m_FeetPos.x + 13,m_FeetPos.y + 32 },
				Point2f{ m_FeetPos.x + 13,m_FeetPos.y }, hit_info))
			{
				m_VelocityY = 0;
				m_Position.y = hit_info.intersectPoint.y;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				if (m_VelocityX == 0)
				{
					m_IsOnMovingPlatform = true;
				}

				break;
			}

			m_IsOnMovingPlatform = false;

		}

	}

#pragma endregion


#pragma region Friction and orientation. Hit timer

	//simulates ground friction 
	if (m_IsGrounded == true)
	{
		m_VelocityX -= (m_VelocityX * 5) * elapsedSec;
	}

	//simulates air friction
	else
	{
		m_VelocityX -= (m_VelocityX / 8) * elapsedSec;
	}

	//Stops movement once it falls below a certain range
	if (m_VelocityX < 10 && m_VelocityX > 0 || m_VelocityX > -10 && m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}


	//Check if Entity is facing right
	if (m_IsHit == false)
	{
		if (m_IsHoldingEgg == false)
		{
			if (m_VelocityX < 0)
			{
				m_IsFacingRight = false;
			}

			else if (m_VelocityX > 0)
			{
				m_IsFacingRight = true;
			}
		}
	}
	else
	{
		m_HitTimer += elapsedSec;

		for (int idx{ 0 }; idx < 11; idx++)
		{
			if (m_HitTimer > 0.1)
			{
				m_HitTimer = 0;
			}

			if (idx > 9)
			{
				m_IsHit = false;
			}
		}




	}


#pragma endregion
}

void Yoshi::Sound(SoundManager*& soundManager) 
{
	if (m_PlayJumpSFX == true)
	{
		soundManager->PlaySFX(SoundManager::YoshiSFX::JumpSFX);

		m_PlayJumpSFX = false;
	}
	if (m_PlayTongueSFX == true)
	{
		soundManager->PlaySFX(SoundManager::YoshiSFX::TongueSFX);

		m_PlayTongueSFX = false;
	}
}

void Yoshi::Animate(const float elapsedSec)
{

	////////////////////////////////////
	// CHECK CURRENT ANIMATION STATE //
	//////////////////////////////////

	if (m_VelocityX == 0 && m_VelocityY == 0)
	{
		m_CurrentState = AnimState::Idle;

	}

	if (m_VelocityX > 0 && m_VelocityX < 260 && m_VelocityY == 0 || m_VelocityX < 0 && m_VelocityX > -260 && m_VelocityY == 0)
	{
		m_CurrentState = AnimState::Walking;
	}

	if (m_VelocityX > 260 && m_VelocityY == 0 || m_VelocityX < -260 && m_VelocityY == 0)
	{
		m_CurrentState = AnimState::Sprinting;
	}

	if (m_IsTonguing == true)
	{
		m_CurrentState = AnimState::Tongue;
	}

	if (m_IsMouthFull == true)
	{
		if (m_VelocityX == 0)
		{
			m_CurrentState = AnimState::FullIdle;

		}

		if (m_VelocityX > 0 && m_VelocityX < 260 || m_VelocityX < 0 && m_VelocityX > -260)
		{
			m_CurrentState = AnimState::FullWalking;
		}

		if (m_VelocityX > 260 || m_VelocityX < -260)
		{
			m_CurrentState = AnimState::FullSprinting;
		}
	}

	if (m_IsHoldingEgg == true)
	{
		if (m_VelocityX == 0)
		{
			m_CurrentState = AnimState::AimIdle;

		}

		if (m_VelocityX > 0 && m_VelocityX < 260 || m_VelocityX < 0 && m_VelocityX > -260)
		{
			m_CurrentState = AnimState::AimWalking;
		}

	}

	if (m_IsLayingEgg == true)
	{
		m_CurrentState = AnimState::LayingEgg;
	}

	if (m_IsPushing == true)
	{
		m_CurrentState = AnimState::Pushing;
	}

	////////////////////////////////////
	// ANIMATIONS FOR CURRENT STATE  //
	//////////////////////////////////


	//Animations for Idle State
	if (m_CurrentState == AnimState::Idle)
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 29;
		}

		m_TxtWidth = 27;
		m_TxtHeight = 32;
		m_YTxtPos = 482;
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

		m_LastState = AnimState::Idle;
	}

	//Animate for Walking state
	if (m_CurrentState == AnimState::Walking)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = AnimState::Walking;
	}

	//Animate for Sprinting State
	if (m_CurrentState == AnimState::Sprinting)
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 2;
		}
		
		m_TxtWidth = 36;
		m_TxtHeight = 26;
		m_YTxtPos = 703;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.05)
		{
			m_XTxtPos += m_TxtWidth + 2;
			m_FrameTime = 0;

		}

		if (m_XTxtPos >= m_TxtWidth * 2 + 2)
		{
			m_XTxtPos = 2;
		}

		m_LastState = AnimState::Sprinting;
	}

	//Animate for Tonguing State
	if (m_CurrentState == AnimState::Tongue)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = m_CurrentState;
	}

	if (m_CurrentState == AnimState::Jumping)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = m_CurrentState;
	}

	if (m_CurrentState == AnimState::Hovering)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = m_CurrentState;
	}

	if (m_CurrentState == AnimState::Pushing)
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 2;
			m_FrameTime = 0;
		}

		m_YTxtPos = 1291;
		m_TxtHeight = 30;
		m_TxtWidth = 29;
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.1)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos > 2 + m_TxtWidth * 4)
		{
			m_XTxtPos = 2;
		}

		m_LastState = m_CurrentState;
	}

	if (m_CurrentState == AnimState::FullIdle)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = AnimState::FullIdle;
	}

	//Animate for Walking state
	if (m_CurrentState == AnimState::FullWalking)
	{
		if (m_LastState != m_CurrentState)
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

		m_LastState = AnimState::FullWalking;
	}

	//Animate for Sprinting State
	if (m_CurrentState == AnimState::FullSprinting)
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 723;
		}


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

		m_LastState = AnimState::Sprinting;
	}

	if (m_CurrentState == AnimState::LayingEgg)
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 2;
		}

		m_TxtWidth = 29;
		m_TxtHeight = 35;
		m_YTxtPos = 1061;
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.1)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos > 29 * 7 + 2)
		{
			m_CurrentState = AnimState::Idle;

			m_IsLayingEgg = false;
		}

		m_LastState = m_CurrentState;
	}

	if (m_CurrentState == AnimState::AimIdle )
	{
		if (m_LastState != m_CurrentState)
		{
			m_XTxtPos = 2;
		}

		m_TxtWidth = 29;
		m_TxtHeight = 35;
		m_YTxtPos = 1061;
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.2)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (m_XTxtPos > 29 * 7 + 2)
		{
			m_CurrentState = AnimState::Idle;

			m_IsLayingEgg = false;
		}

		m_LastState = m_CurrentState;

	}

	if (m_CurrentState == AnimState::AimWalking)
	{


	}

	if (m_CurrentState == AnimState::AimFluttering)
	{
		
	}

	for (int idx = 0; idx < m_Eggs.size(); idx++)
	{
		if (m_IsHoldingEgg == true)
		{
			if (m_Eggs[idx] != m_Eggs.back())
			{
				m_Eggs[idx]->Animate(elapsedSec);
			}
		}

		else
		{
			m_Eggs[idx]->Animate(elapsedSec);
		}
		
	}
}

void Yoshi::KeysDown()
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(nullptr);
	if (pKeyStates[SDL_SCANCODE_LEFT])
	{
		if (m_VelocityX > -280)
		{
			m_VelocityX -= 11 ;
		}
	}
	if (pKeyStates[SDL_SCANCODE_RIGHT])
	{
		if (m_VelocityX < 280)
		{
			m_VelocityX += 11;
		}
	}
	if (pKeyStates[SDL_SCANCODE_UP])
	{
		m_IsLookingUp = true;
	}
	if (pKeyStates[SDL_SCANCODE_DOWN])
	{
		if (m_IsMouthFull == true)
		{
			if (m_Eggs.size() < 6)
			{
				m_Eggs.push_back(new Egg(m_Position));
			}

			m_IsMouthFull = false;
			m_IsLayingEgg = true;
		}

		m_IsCrouching = true;
	}
	if (pKeyStates[SDL_SCANCODE_Z])
	{
		m_IsYoshiJumping = true;
		m_CurrentState = AnimState::Jumping;

	}
	if (pKeyStates[SDL_SCANCODE_X])
	{
		if (m_IsTongueReady == true)
		{
			m_PlayTongueSFX = true;

			if (m_IsMouthFull == false)
			{
				m_IsTonguing = true;
				m_IsTongueReady = false;
			}

			else
			{
				m_IsEnemySpitOut = true;
				m_IsTongueReady = false;
			}
		}
		
	}
	//TODO debug keys remove later
	if (pKeyStates[SDL_SCANCODE_SPACE])
	{
		m_Position.y += 5;
	}
	if (pKeyStates[SDL_SCANCODE_RSHIFT])
	{
		m_Position.y -= 5;
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
		m_IsCrouching = false;
		break;
	case SDLK_UP:

		m_IsLookingUp = false;

		break;

	case SDLK_x:
		m_IsTonguing = false;
		break;
	case SDLK_c:

		if (m_IsHoldingEgg == false)
		{
			if (m_Eggs.size() > 0)
			{
				if (m_Eggs.back()->GetIsThrown() == false)
				{
					m_IsHoldingEgg = true;
				}

			}
		}

		else if (m_IsHoldingEgg == true)
		{
			if (m_Eggs.size() > 0)
			{
				m_IsHoldingEgg = false;
				m_Eggs.back()->ThrowEgg();
			}
		}
		break;

	case SDLK_v:

		m_IsCalculatingAngle = !m_IsCalculatingAngle;
		break;

	case SDLK_ESCAPE:
		m_PlayerPause = !m_PlayerPause;
		break;
	}
}

void Yoshi::Debug() 
{
	//collision and gravity
	m_Position.y += m_VelocityY / 100;

	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX / 100;
}

void Yoshi::HitCheck(const std::vector<Enemy*>& enemies, std::vector<Entity*>& lvlEntities, Rectf marioHitbox)
{
	if (!enemies.empty())
	{
		if (m_IsHit == false)
		{
			for (int idx{ 0 }; idx < enemies.size(); idx++)
			{
				if (enemies[idx]->GetIsActive() == true)
				{
					if (enemies[idx]->GetIsSpat() == false)
					{
						if (enemies[idx]->GetIsSwallowed() == false)
						{
							//checks if enemy is "squashable" and if the yoshi hits his head kills him
							if (enemies[idx]->GetIsSquashable() == true)
							{
								if (utils::IsOverlapping(m_Hitbox, enemies[idx]->GetHitBox()) == true)
								{
									if (m_Hitbox.bottom > enemies[idx]->GetHitBox().bottom + enemies[idx]->GetHitBox().height - 3)
									{
										enemies[idx]->EnemyDeath();
										m_VelocityY *= -2.f;

										break;
									}
								}
							}

							//checks if enemy can be eaten and if the tongue hits him it eats him
							if (enemies[idx]->GetIsEdible() == true)
							{
								if (utils::IsOverlapping(enemies[idx]->GetHitBox(), m_Tongue) == true)
								{
									enemies[idx]->EnemySwallowed();
									m_IsMouthFull = true;
									break;
								}
							}

							//checks if egg hit the enemy
							if (!m_Eggs.empty())
							{
								if (m_Eggs.back()->GetIsThrown() == true)
								{
									if (utils::IsOverlapping(m_Eggs.back()->GetHitBox(), enemies[idx]->GetHitBox()) == true)
									{
										enemies[idx]->EnemyDeath();
										m_Eggs.pop_back();
										break;
									}
								}
							}

							//checks if enemy his hitting yoshi

							if (utils::IsOverlapping(m_Hitbox, enemies[idx]->GetHitBox()) == true)
							{
								m_IsHit = true;

								if (enemies[idx]->GetIsFacingRight() == true)
								{
									m_VelocityX *= -1.f;
									m_VelocityX -= 300.f;

								}

								else
								{
									m_VelocityX *= -1.f;
									m_VelocityX += 300.f;
								}

								m_VelocityY += 100;

								m_IsMarioOn = false;

								break;
							}
						}
					}

				}

			}
		}

		if (m_IsMarioOn == false)
		{
			if (utils::IsOverlapping(m_Hitbox, marioHitbox) == true)
			{
				m_IsMarioOn = true;
			}
		}
	}

	if (!lvlEntities.empty())
	{
		for (int idx{ 0 }; idx < lvlEntities.size(); idx++)
		{
			if (lvlEntities[idx] != nullptr)
			{
				if (lvlEntities[idx]->GetIsActive() == true)
				{
					if (const auto wingedClouds = dynamic_cast<::WingedClouds*>(lvlEntities[idx]))
					{
						if (!m_Eggs.empty())
						{
							if (m_Eggs.back()->GetIsThrown() == true)
							{
								if (utils::IsOverlapping(m_Eggs.back()->GetHitBox(), wingedClouds->GetHitBox()) == true)
								{
									wingedClouds->SetIsHit();
									m_Eggs.pop_back();
									break;
								}
							}
						}
					}

					if (utils::IsOverlapping(m_Hitbox, lvlEntities[idx]->GetHitBox()))
					{
						if (const auto flowers = dynamic_cast<::Flower*>(lvlEntities[idx]))
						{
							lvlEntities[idx]->FlipIsActive();

							m_Flowers += 1;
							break;
						}

						if (const auto coins = dynamic_cast<::Coin*>(lvlEntities[idx]))
						{
							if (coins->GetIsRedCoin() == true)
							{
								m_RedCoins += 1;
							}
							else
							{
								m_Coins += 1;
							}
							lvlEntities[idx]->FlipIsActive();
							break;
						}

						if (const auto stars = dynamic_cast<::Star*>(lvlEntities[idx]))
						{
							if (m_MarioTimer < 20)
							{
								m_MarioTimer += 1;
							}

							lvlEntities[idx]->FlipIsActive();
							break;
						}

						if (const auto boulder = dynamic_cast<::Boulder*>(lvlEntities[idx]))
						{
							if (m_Position.y > boulder->GetPosition().y + 30)
							{
								m_IsStandingOnEntity = true;
								m_LvlEntityTop = boulder->GetHitBox().bottom + boulder->GetHitBox().height + 1;
								break;
							}

							if (m_Position.x < boulder->GetPosition().x || m_Position.x > boulder->GetPosition().x)
							{
								m_VelocityX /= 3;
								m_IsPushing = true;
								m_PushTimer = 0;
								boulder->AddVelocity(m_VelocityX / 5, 0);
								break;
							}
						}

						if (const auto blocks = dynamic_cast<::Block*> (lvlEntities[idx]))
						{
							if (blocks->GetIsBlockHit() == false)
							{
								if (m_Position.y > blocks->GetPosition().y + 30)
								{
									m_IsStandingOnEntity = true;
									m_LvlEntityTop = blocks->GetHitBox().bottom + blocks->GetHitBox().height;
									break;
								}

								if (m_Position.y + m_TxtWidth * 2 < blocks->GetPosition().y)
								{
									if (m_Eggs.size() < 6)
									{
										blocks->BlockHit(m_Eggs);
										m_VelocityY = 0;
										m_FlightTime = 1;
									}

									else
									{
										m_VelocityY = 0;
										m_FlightTime = 1;
									}
									break;
								}

								if (m_Position.x < blocks->GetPosition().x || m_Position.x > blocks->GetPosition().x)
								{
									m_VelocityX = 0;
									break;
								}
							}


						}


					}

					m_IsStandingOnEntity = false;
				}

			}

		}

	}

	for (int idx{ 0 }; idx < m_Eggs.size(); idx++)
	{
		if (m_Eggs[idx]->GetIsFallen())
		{
			if (utils::IsOverlapping(m_Hitbox,m_Eggs[idx]->GetHitbox()))
			{
				m_Eggs[idx]->PickUpEgg();
			}
		}
	}
	

}

void Yoshi::EmptyMouth()
{
	m_IsMouthFull = false;
	m_IsEnemySpitOut = false;
}

bool Yoshi::GetIsMarioOn() const
{
	return m_IsMarioOn;
}

bool Yoshi::GetIsJumping() const
{
	return m_IsYoshiJumping;
}

bool Yoshi::GetIsHovering() const
{
	if (m_CurrentState == AnimState::Hovering)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Yoshi::GetIsCrouching() const
{
	return m_IsCrouching;
}

bool Yoshi::GetIsLookingUp() const
{
	return m_IsLookingUp;
}

bool Yoshi::GetPlayerPause() const
{
	return m_PlayerPause;
}

bool Yoshi::GetIsEnemySpatOut() const
{
	return m_IsEnemySpitOut;
}

bool Yoshi::GetIsOnMovingPlatform() const
{
	return m_IsOnMovingPlatform;
}


