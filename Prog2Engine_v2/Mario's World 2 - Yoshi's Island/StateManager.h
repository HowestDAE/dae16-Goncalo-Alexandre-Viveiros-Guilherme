#pragma once
class Texture;

class StateManager
{
public:
	enum class States
	{
		Intro,
		StartMenu,
		LevelSelector,
		Gameplay,
		LevelPause,
		Pause,
		DeathMenu,
		ResultsMenu,
		BonusLevels
	};

	StateManager();
	~StateManager();
	StateManager(const StateManager& rhs) = delete;
	StateManager& operator=(const StateManager& rhs) = delete;
	StateManager(StateManager&& rhs) = delete;
	
	States GetState();
	void SetState(States state);
	void Draw() const;
	void Update(int coins,int redCoins,int flowers,int stars, bool hasYoshiLost);
	void SetPointerPosition(int pointerPosX);
	int GetPointerPositionX() const;
private:
	States m_CurrentState;
	Texture* m_LevelSelTex1;
	Texture* m_LevelSelTex2;
	Texture* m_PauseScreenBG;
	Texture* m_PauseScreenIcons;
	Texture* m_DeathScreen;

	int m_Lives{ 3 };
	int m_Coins{ 0 };
	int m_RedCoins{ 0 };
	int m_Flowers{ 0 };
	int m_Stars{ 0 };
	int m_PointerPosX{ 0 };
};

