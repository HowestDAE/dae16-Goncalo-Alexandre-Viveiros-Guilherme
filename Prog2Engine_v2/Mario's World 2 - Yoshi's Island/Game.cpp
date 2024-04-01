#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Texture.h"
#include "Yoshi.h"
#include "utils.h"
#include "SVGParser.h"
#include "Camera.h"
#include "Level.h"


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
	m_Level01 = new Level ("1-1 Make Eggs Throw Eggs no coins.png","ChocolateMountainsWIP.png");
	m_YoshiPlyr = new Yoshi(Point2f(130,400));
	SVGParser::GetVerticesFromSvgFile("ex3.svg",m_LvlVertices);
	m_GameCam = new Camera(Point2f(0, 0), m_YoshiPlyr->GetYoshiPos());
}

void Game::Cleanup( )
{
	delete m_Level01;
	delete m_YoshiPlyr;
}

void Game::Update( float elapsedSec )
{
	m_YoshiPlyr->Update(m_LvlVertices,elapsedSec);
	m_YoshiPlyr->Animation(elapsedSec);


	
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
	glPushMatrix();
	{
		glTranslatef(m_GameCam->Pan(m_YoshiPlyr->GetYoshiPos()).x, m_GameCam->Pan(m_YoshiPlyr->GetYoshiPos()).y -90, 0);

		glPushMatrix();

		glPushMatrix();

		glTranslatef(-m_GameCam->Pan(m_YoshiPlyr->GetYoshiPos()).x/2, -m_GameCam->Pan(m_YoshiPlyr->GetYoshiPos()).y +90 /2, 0); //parallax scrolling
		m_Level01->DrawBackground();

		glPopMatrix();

			glScalef(1.959676875, 1.9868859, 0);
			glTranslatef(0,-430 , 0);
			m_Level01->DrawLvl();

		glPopMatrix();

		m_YoshiPlyr->Draw();
	}
	glPopMatrix();

	

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_YoshiPlyr->Controls(e);

	//switch (e.keysym.sym)
	//{

	//case SDLK_w:
	//	yCam -= 10;
	//	break;
	//case SDLK_a:
	//	xCam += 10;
	//	break;
	//case SDLK_s:
	//	yCam += 10;
	//	break;
	//case SDLK_d:
	//	xCam -= 10;
	//	break;
	//}

	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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
