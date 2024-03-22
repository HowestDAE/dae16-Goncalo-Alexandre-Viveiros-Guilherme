#pragma once
#include "BaseGame.h"
#include <vector>

class Yoshi;
class Texture;
class Level;
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

	float xCam{ 0 };
	float yCam{ 0 };

	Point2f lastCamPos{ 0,0 };
	Point2f currentCamPos{ xCam,yCam };

	int m_LevelStartX{0};
	int m_LevelStartY{-430};
	Level* m_Level01;
	Yoshi* m_YoshiPlyr;
	std::vector< std::vector<Point2f>> m_LvlVertices{};
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};