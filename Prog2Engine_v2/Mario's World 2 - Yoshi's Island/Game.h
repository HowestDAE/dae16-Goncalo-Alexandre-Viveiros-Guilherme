#pragma once
#include "BaseGame.h"

class StateManager;
class EnemyManager;
class Yoshi;
class Camera;
class Level;
class Mario;
class SoundManager;
class UI;
class Game final : public BaseGame
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
	void Reset()const;

private:
	StateManager* m_StateManager;
	Level* m_Level01;
	Yoshi* m_YoshiPlyr;
	Mario* m_Mario;
	Camera* m_GameCam;
	EnemyManager* m_EnemyManager;
	SoundManager* m_SoundManager;
	UI* m_UI;
	bool debugging {false};
	bool noclip{ false };
	// FUNCTIONS
	void Initialize();
	void Cleanup( ) const;
	void ClearBackground( ) const;
};