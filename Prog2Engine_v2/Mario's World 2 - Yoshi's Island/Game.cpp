#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Texture.h"
#include "Yoshi.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "FlyingShyGuy.h"
#include "Level.h"
#include "Mario.h"
#include "PiranhaPlant.h"
#include "PogoShyGuy.h"
#include "ShyGuy.h"
#include "WalkingTulip.h"


Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Level01 = new Level ("1-1 Make Eggs Throw Eggs no coins.png","ChocolateMountainsWIP.png","Gradient_BG.png",0,Point2f(7300,633),1 );
	m_YoshiPlyr = new Yoshi(Point2f(130,280));
	m_Mario = new Mario(m_YoshiPlyr);
	m_GameCam = new Camera(Point2f(0, 0), m_YoshiPlyr->GetPosition());
	m_EnemyManager = new EnemyManager();

	m_EnemyManager->SpawnEnemies(1);
}

void Game::Cleanup() const
{
	delete m_Level01;
	delete m_YoshiPlyr;
	delete m_GameCam;
	delete m_Mario;
	delete m_EnemyManager;
}

void Game::Update(const float elapsedSec )
{

	//Levels Functions
	m_Level01->Update(elapsedSec,m_YoshiPlyr->GetPlayerPause(),m_YoshiPlyr);


	//std::cout << 1 / elapsedSec << "\n";
	if (m_Level01->GetLevelPause() == false)
	{
		

		if (m_YoshiPlyr->GetPlayerPause() == false)
		{
			//Level Functions
			m_Level01->WarpPipesUpdate(true, m_YoshiPlyr, Point2f(2708, 348), 16, 16, Point2f(740, -515), m_GameCam);
			m_Level01->LevelEndUpdate(m_YoshiPlyr->GetPosition());
			m_Level01->Animate(elapsedSec);

			//Yoshis functions
			if (noclip == false)
			{
				m_YoshiPlyr->Update(m_Level01->GetLevelVertices(), m_Level01->GetPlatformVertices(), elapsedSec);
			}
			else
			{
				m_YoshiPlyr->Debug();
			}
			m_YoshiPlyr->Animate(elapsedSec);
			m_YoshiPlyr->HitCheck(m_EnemyManager->GetEnemyVector(), m_Level01->GetWingedClouds(), m_Mario->GetHitBox(), m_Level01->GetFlowers());
			m_YoshiPlyr->KeysDown();

			//Camera functions
			m_GameCam->Pan(m_YoshiPlyr, m_Level01->GetLevelStart(), m_Level01->GetLevelEnd().x);

			//Mario's functions
			m_Mario->Update(m_Level01->GetLevelVertices(), elapsedSec);
			m_Mario->Animate(elapsedSec);

			//Enemy Functions
			m_EnemyManager->Update(m_Level01->GetLevelVertices(), elapsedSec,m_YoshiPlyr->GetPosition());
		}
		
	

	}


	if (debugging == true)
	{
		std::cout << "X Position" << m_YoshiPlyr->GetPosition().x << "\n" << "Y Position" <<m_YoshiPlyr->GetPosition().y ;
	}
		
	
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
	{
		glTranslatef(m_GameCam->GetCamPos().x, m_GameCam->GetCamPos().y, 0);

		glPushMatrix();

		glTranslatef(-m_GameCam->GetCamPos().x / 2, -m_GameCam->GetCamPos().y / 2, 0);          //parallax scrolling
		m_Level01->DrawBackground();

		glPopMatrix();

		glPushMatrix();

		glScalef(1.959676875, 1.9868859, 0);
		glTranslatef(0, -430, 0);
		m_Level01->DrawLvl();
		glPopMatrix();

		m_Level01->DrawOthers();
		m_Mario->Draw();
		m_YoshiPlyr->Draw();
		m_EnemyManager->Draw();

	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
	switch (e.keysym.sym)
	{
	case SDLK_r:
		m_EnemyManager->AddEnemy(m_YoshiPlyr->GetPosition(), m_YoshiPlyr->GetIsFacingRight());
		break;
	case SDLK_d:
		debugging = !debugging;
		break;
	case SDLK_n:
		noclip = !noclip;
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_YoshiPlyr->KeysUp(e);

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
