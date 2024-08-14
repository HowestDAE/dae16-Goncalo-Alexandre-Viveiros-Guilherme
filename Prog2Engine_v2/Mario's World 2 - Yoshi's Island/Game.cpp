#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Texture.h"
#include "Yoshi.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "Level.h"
#include "Mario.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "UI.h"

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
	m_StateManager = new StateManager();
	m_Level01 = new Level ("1-1 Make Eggs Throw Eggs no coins.png","ChocolateMountainsWIP.png","WaterFallCave.png",
		"Gradient_BG.png",0,Point2f(7300,633),1, m_StateManager);
	m_YoshiPlyr = new Yoshi(Point2f(130,280));
	m_Mario = new Mario(m_YoshiPlyr);
	m_GameCam = new Camera(Point2f(0, 0));
	m_EnemyManager = new EnemyManager();
	m_SoundManager = new SoundManager();
	m_UI = new UI("MarioTimer.png", 32, 32);
	m_EnemyManager->SpawnEnemies(1);
}

void Game::Cleanup() const
{
	delete m_StateManager;
	delete m_Level01;
	delete m_YoshiPlyr;
	delete m_GameCam;
	delete m_Mario;
	delete m_EnemyManager;
	delete m_SoundManager;
	delete m_UI;
}

void Game::Update(const float elapsedSec )
{
	if (m_StateManager->GetState() == StateManager::States::Gameplay || m_StateManager->GetState() == StateManager::States::LevelPause || m_StateManager->GetState() == StateManager::States::Pause)
	{
		//Levels Functions
		m_Level01->Update(elapsedSec, m_YoshiPlyr, m_EnemyManager->GetEnemyVector(), m_SoundManager, m_GameCam);


		if (m_StateManager->GetState() == StateManager::States::Gameplay || m_StateManager->GetState() == StateManager::States::LevelPause)
		{

			if (m_StateManager->GetState() == StateManager::States::Gameplay)
			{
				//Level Functions
				m_Level01->LevelEndUpdate(m_YoshiPlyr->GetPosition());

				//Yoshis functions
				if (noclip == false)
				{
					m_YoshiPlyr->Update(m_Level01->GetLevelVertices(), m_Level01->GetPlatformVertices(), m_SoundManager, elapsedSec);
					m_UI->Update(m_YoshiPlyr->GetIsMarioOn(), m_YoshiPlyr->GetMarioTimer());
				}
				else
				{
					m_YoshiPlyr->Debug();
				}
				m_YoshiPlyr->HitCheck(m_EnemyManager->GetEnemyVector(), m_Level01->GetLevelEntities(), m_Mario->GetHitBox());
				m_YoshiPlyr->KeysDown();

				//Camera functions
				m_GameCam->Pan(m_YoshiPlyr, m_Level01->GetLevelStart(), m_Level01->GetLevelEnd().x);

				//Mario's functions
				m_Mario->Update(m_Level01->GetLevelVertices(), m_SoundManager,elapsedSec);

				//Enemy Functions
				m_EnemyManager->Update(m_Level01->GetLevelVertices(), elapsedSec, m_YoshiPlyr, m_Level01->GetLevelEntities(), m_SoundManager, m_Mario);
			}

		}

		//std::cout << 1 / elapsedSec << "\n"; //FPS


		if (debugging == true)
		{
			std::cout << "X Position" << m_YoshiPlyr->GetPosition().x << "\n" << "Y Position" << m_YoshiPlyr->GetPosition().y;
		}
	}

	if (m_StateManager->GetState() != StateManager::States::Gameplay)
	{
		m_Level01->PauseMusic(m_SoundManager);
	}

	m_StateManager->Update(m_YoshiPlyr->GetCoinsAmount(), m_YoshiPlyr->GetRedCoinsAmount(), m_YoshiPlyr->GetFlowersAmount(), m_YoshiPlyr->GetStarsAmount(),m_EnemyManager->GetHasYoshiLost());

	if (m_StateManager->GetResetGameplay() == true)
	{
		Reset();
		m_StateManager->TurnOffResetGameplay();
	}
}

void Game::Draw( ) const
{
	if (m_StateManager->GetState() != StateManager::States::Gameplay || m_StateManager->GetState() == StateManager::States::LevelPause)
	{
		ClearBackground();

		m_StateManager->Draw();

	}

	if (m_StateManager->GetState() == StateManager::States::Gameplay || m_StateManager->GetState() == StateManager::States::LevelPause)
	{
		ClearBackground();

		glPushMatrix();
		{
			glTranslatef(m_GameCam->GetCamPos().x, m_GameCam->GetCamPos().y, 0);
			m_Level01->DrawLvl(m_GameCam->GetCamPos());
			m_Mario->Draw();
			m_YoshiPlyr->Draw();
			m_EnemyManager->Draw();
			m_UI->Draw(m_GameCam->GetCamPos());
		}
		glPopMatrix();
	}


}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_YoshiPlyr->KeysUp(e);

	m_StateManager->Keys(e);

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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::Reset () const
{
	m_Level01->Reset();
	m_YoshiPlyr->Reset();
	m_Mario->Reset();
	m_GameCam->Reset();
	m_EnemyManager->Reset();
	m_UI->Reset();

}
