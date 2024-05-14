#pragma once
#include "BaseGame.h"
#include <vector>


class Platforms;
class Enemy;
class ShyGuy;
class Yoshi;
class Camera;
class Texture;
class Level;
class Mario;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	Level* m_Level01;
	Platforms* m_Platforms;
	Yoshi* m_YoshiPlyr;
	Mario* m_Mario;
	Camera* m_GameCam;
	ShyGuy* m_ShyGuy1;
	std::vector<Enemy*> m_Enemies;
	// FUNCTIONS
	void Initialize();
	void Cleanup( ) const;
	void ClearBackground( ) const;
};