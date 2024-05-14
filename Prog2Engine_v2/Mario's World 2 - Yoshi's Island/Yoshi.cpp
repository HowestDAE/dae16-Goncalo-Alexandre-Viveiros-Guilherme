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

	Entity::Draw();

#pragma region Debug
	//utils::SetColor(Color4f{ 1,0,0,1 });
	//////left side
	//utils::DrawLine(Point2f{ m_FeetPos.x - 13,m_FeetPos.y +32 },
	//	Point2f{ m_FeetPos.x - 13,m_FeetPos.y });			 
	//utils::DrawLine(Point2f{ m_FeetPos.x + 13,m_FeetPos.y +32 },
	//	Point2f{ m_FeetPos.x + 13,m_FeetPos.y });

	//utils::SetColor(Color4f{ 0,1,0,1 });
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
#pragma endregion


	if (m_IsTonguing == true)
	{
		if (m_IsFacingRight == true)
		{
			m_EntityTxt->Draw(Rectf(m_Position.x + m_TxtWidth * 2, m_Position.y + m_TxtHeight, 250 * m_FrameTime, 5), Rectf(41, 962, 8, 3));
			m_EntityTxt->Draw(Rectf{ m_Tongue.center.x,m_Tongue.center.y,8,7 }, Rectf{ 32 ,964,8,7 });
		}
		else
		{
			m_EntityTxt->Draw(Rectf(m_Tongue.center.x, m_Position.y + m_TxtHeight, 250*m_FrameTime, 5), Rectf(41, 962, 8, 3));
			m_EntityTxt->Draw(Rectf{ m_Tongue.center.x,m_Tongue.center.y,8,7 }, Rectf{ 32 ,964,8,7 });
		}
	}

}

void Yoshi::Update(const std::vector<std::vector<Point2f>>& platforms, const float elapsedSec)
{
	//updates Yoshis Feet position
	if (m_IsFacingRight == true)
	{
		m_FeetPos = Point2f{ m_Position.x + 19, m_Position.y - 3};
	}
	else
	{
		m_FeetPos = Point2f{ m_Position.x + 39,m_Position.y-3};
	}
	
	//Update Hitbox
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));



#pragma region Collision

	utils::HitInfo hit_info;

	//Collisions

	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{
		//floor collision

	//checks collision from the left side of Yoshis feet

		if (utils::Raycast(platforms[idx], Point2f{m_FeetPos.x - 13,m_FeetPos.y + 32},
			Point2f{ m_FeetPos.x - 13,m_FeetPos.y}, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

    //checks collision from the right side of Yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 13,m_FeetPos.y + 32},
			Point2f{ m_FeetPos.x + 13,m_FeetPos.y }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

		//checks collision from the middle of Yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x ,m_FeetPos.y + 32 },
			Point2f{ m_FeetPos.x ,m_FeetPos.y }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

		//Gravity
		else
		{
			m_IsGrounded = false;

			if (m_VelocityY != -480.f)
			{
				m_VelocityY -= 48.f ;

				if (m_VelocityY < -480.f)
				{
					m_VelocityY -= -50.f;
				}
			}



		}

		//Wall Collision

		if (m_IsFacingRight == true)
		{
			//left side
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 6,m_Position.y + 32 },
				Point2f{ m_FeetPos.x - 15,m_Position.y + 32 }, hit_info))
			{
				m_Position.x = hit_info.intersectPoint.x; //Teleports entity to the point of intersection with a small offset
			}

			//right side
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x + 6,m_Position.y + 32 },
				Point2f{ m_FeetPos.x + 15,m_Position.y + 32 }, hit_info))
			{
				m_Position.x = hit_info.intersectPoint.x - 40; //Teleports entity to the point of intersection with a small offset
			}

		}

		else
		{
			//right side
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x -6,m_Position.y + 32 },
				Point2f{ m_FeetPos.x + 15,m_Position.y + 32 }, hit_info))
			{
				m_Position.x = hit_info.intersectPoint.x - 60; //Teleports entity to the point of intersection with a small offset
			}

			//left side
			if (utils::Raycast(platforms[idx], Point2f{ m_FeetPos.x - 6,m_Position.y + 32 },
				Point2f{ m_FeetPos.x - 15,m_Position.y + 32 }, hit_info))
			{
				m_Position.x = hit_info.intersectPoint.x - 19; //Teleports entity to the point of intersection with a small offset
			}


		}


	}

#pragma endregion

	


#pragma region Friction and orientation

	//simulates ground friction 
	if (m_IsGrounded == true)
	{
		m_VelocityX -= (m_VelocityX * 5) * elapsedSec;
	}

	//simulates air friction
	else
	{
		m_VelocityX -= (m_VelocityX/ 5) * elapsedSec;
	}

	//Stops movement once it falls below a certain range
	if (m_VelocityX < 20 && m_VelocityX > 0 || m_VelocityX > -20 && m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}


	//Check if Entity is facing right
	
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
	

#pragma endregion
	
	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;

#pragma region Jump

	if (m_IsYoshiJumping == true)
	{
		if (m_VelocityY < 200)
		{
			m_IsJumpDone = true;
		}

		if (m_IsGrounded == true)
		{
			m_FlightTime = 0;

			m_Position.y += 20;

			m_VelocityY += 1400.f;

			
		}

		else
		{
			if (m_IsJumpDone == true)
			{
				if (m_VelocityY < 0)
				{
					m_FlightTime += elapsedSec;

					if (m_FlightTime < 0.8)
					{
						m_CurrentState = AnimState::Hovering;
						m_VelocityY = 30.f;

						if (m_FlightTime > 0.75)
						{
							m_VelocityY = 200.f;
						}
					}
				}
				
			}
		}
		
	}

	else
	{
		if (m_VelocityY < 0)
		{

			if (m_IsYoshiJumping == true)
			{
				m_FlightTime += elapsedSec;

				if (m_FlightTime < 0.8)
				{
					m_CurrentState = AnimState::Hovering;
					m_VelocityY = 30.f;

					if (m_FlightTime > 0.75)
					{
						m_VelocityY = 200.f;
					}
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
			m_Tongue.center.x = (m_Position.x + m_TxtWidth*2) + 250 * m_FrameTime;
		}

		else
		{
			m_Tongue.center.x = m_Position.x - 250 * m_FrameTime;
		}
	}

	else if (m_IsTonguing == false)
	{
		m_Tongue.center.x = m_Position.x;
		m_Tongue.center.y = m_Position.y + m_TxtHeight;
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
				m_MarioTimer -= 1;
				m_Countdown = 0;
			}
		}
		
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

	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;
	//Update Hitbox

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

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
	}

	if (m_IsHoldingEgg == true)
	{
		m_Eggs.back()->HoldEgg(m_Hitbox, m_IsFacingRight,m_IsCalculatingAngle,m_IsThrown,elapsedSec);
		if (m_IsCrouching == true) { m_IsHoldingEgg = false; }
		if (m_IsTonguing == true) { m_IsHoldingEgg = false; }

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
			m_VelocityX -= 28;
		}
	}
	if (pKeyStates[SDL_SCANCODE_RIGHT])
	{
		if (m_VelocityX < 280)
		{
			m_VelocityX += 28;
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
			m_Eggs.push_back(new Egg(m_Position));

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
		if (m_IsMouthFull == false)
		{
			m_IsTonguing = true;
		}
		else
		{
			//TODO add a functiom that throws the eaten enemy
		}
	}
	if (pKeyStates[SDL_SCANCODE_C])
	{
		if (m_IsHoldingEgg == false)
		{
			if (m_Eggs.size() > 0)
			{
				
				m_IsHoldingEgg = true;

			}
		}

		else
		{
			m_IsThrown = true;
		}

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
		
		break;

	case SDLK_v:

		m_IsCalculatingAngle = !m_IsCalculatingAngle;
		break;
	}
}


void Yoshi::Debug() const
{

	std::cout << m_MarioTimer << "\n";
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
					if (utils::IsOverlapping(Enemies[idx]->GetHitBox(),m_Tongue) == true)
					{
						Enemies[idx]->EnemyDeath();
						Enemies[idx] = nullptr;
						m_IsMouthFull = true;
						m_IsTonguing = false;
					}
				}
			}
			
		}
	}
	
	
}
