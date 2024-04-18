#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Texture.h"
#include "Yoshi.h"
#include "utils.h"
#include "SVGParser.h"
#include "Camera.h"
#include "Level.h"
#include "Mario.h"
#include "ShyGuy.h"


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
	m_Level01 = new Level ("1-1 Make Eggs Throw Eggs no coins.png","ChocolateMountainsWIP.png","Gradient_BG.png");
	m_YoshiPlyr = new Yoshi(Point2f(130,400));
	m_Mario = new Mario(m_YoshiPlyr);
	SVGParser::GetVerticesFromSvgFile("ex3.svg",m_LvlVertices);
	m_GameCam = new Camera(Point2f(0, 0), m_YoshiPlyr->GetPosition());
	m_ShyGuy1 = new ShyGuy(Point2f(550, 400));
	m_Enemies = { m_ShyGuy1};
}

void Game::Cleanup()
{
	delete m_Level01;
	delete m_YoshiPlyr;
	delete m_GameCam;
	delete m_Mario;
}

void Game::Update( float elapsedSec )
{
	//std::cout << 1 / elapsedSec << "\n";

	m_YoshiPlyr->Update(m_LvlVertices,elapsedSec);
	m_YoshiPlyr->Animate(elapsedSec);
	m_YoshiPlyr->HitCheck(m_Enemies);
	m_GameCam->Pan(m_YoshiPlyr->GetPosition(), m_YoshiPlyr->GetIsGrounded(),m_YoshiPlyr->GetIsFacingRight());
	m_Mario->Update(m_LvlVertices,elapsedSec);
	m_Mario->Animate(elapsedSec);
	m_YoshiPlyr->Debug();
	

		
	for(int idx{0};idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx] != nullptr)
		{
		if (auto ShyGuys = dynamic_cast<ShyGuy*>(m_Enemies[idx]))
		{
			ShyGuys->Update(m_LvlVertices, elapsedSec);
			ShyGuys->Animate();
		}
		}

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

	//Draws All elements of the game and uses matrixes to modify them

	//glPushMatrix();
	//{
	//	glTranslatef(m_GameCam->GetCamPos().x, m_GameCam->GetCamPos().y, 0);

	//	glPushMatrix();

	//	glPushMatrix();

	//	glTranslatef(-m_GameCam->GetCamPos().x/2,-m_GameCam->GetCamPos().y/2, 0);          //parallax scrolling
	//	m_Level01->DrawBackground();

	//	glPopMatrix();

	//		glScalef(1.959676875, 1.9868859, 0);
	//		glTranslatef(0,-430 , 0);
	//		m_Level01->DrawLvl();

	//	glPopMatrix();
	//	m_Mario->Draw();
	//	m_YoshiPlyr->Draw();
	//	m_ShyGuy1->Draw();
	//	
	//	
	//}
	//glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_GameCam->GetCamPos().x, m_GameCam->GetCamPos().y, 0);

		glPushMatrix();

		glPushMatrix();

		glTranslatef(-m_GameCam->GetCamPos().x / 2, -m_GameCam->GetCamPos().y / 2, 0);          //parallax scrolling
		m_Level01->DrawBackground();

		glPopMatrix();

		glScalef(1.959676875, 1.9868859, 0);
		glTranslatef(0, -430, 0);
		m_Level01->DrawLvl();
		glPopMatrix();

		m_Mario->Draw();
		m_YoshiPlyr->Draw();

		
		for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
		{
			if (m_Enemies[idx] != nullptr)
			{
			if (auto ShyGuys = dynamic_cast<ShyGuy*>(m_Enemies[idx]))
			{
				ShyGuys->Draw();
			}
			}
		}

	



	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_YoshiPlyr->KeysDown(e);
	switch (e.keysym.sym)
	{
	case SDLK_r:
		m_Enemies.push_back(new ShyGuy(Point2f(m_YoshiPlyr->GetPosition().x + 100, m_YoshiPlyr->GetPosition().y + 100)));
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
