#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Yoshi.h"

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
	m_Level01_BG1 = new Texture ("1-1 Make Eggs Throw Eggs no coins.png");
	m_YoshiPlyr = new Yoshi(Point2f(0,0));

}

void Game::Cleanup( )
{
	delete m_Level01_BG1;
}

void Game::Update( float elapsedSec )
{
	m_YoshiPlyr->Animation(elapsedSec);
	m_YoshiPlyr->Update();

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
		glScalef(2, 2, 0);
		glTranslatef(m_LevelXPos,m_LevelYPos, 0);
		m_Level01_BG1->Draw();
	}
	glPopMatrix();

	m_YoshiPlyr->Draw();

	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	/*
	if (SDL_KEYDOWN == SDLK_DOWN)
	{
		m_LevelYPos += 5;
	}
	if (SDL_KEYDOWN == SDLK_UP)
	{
		m_LevelYPos -= 5;
	}

	if (SDLK_LEFT == true)
	{
		m_LevelYPos += 5;
	}

	if (SDLK_RIGHT == true)
	{
		m_LevelXPos -= 5;
	}
	*/

	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_LevelXPos += 5;
		break;
	case SDLK_RIGHT:
		m_LevelXPos -= 5;
		break;
	case SDLK_UP:
		m_LevelYPos -= 5;
	break;
	case SDLK_DOWN:
		m_LevelYPos += 5;
	}

	
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
