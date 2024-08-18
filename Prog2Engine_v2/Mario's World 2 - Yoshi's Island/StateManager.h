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
	StateManager& operator=(StateManager&& rhs) = delete;
	
	States GetState();
	void SetState(States state);
	void Draw() const;
	void Update(int coins,int redCoins,int flowers,int stars, bool hasYoshiLost);
	void Keys(const SDL_KeyboardEvent& e);
	bool GetResetGameplay();
	void TurnOffResetGameplay();

private:
	States m_CurrentState;
	Texture* m_LevelSelTex1;
	Texture* m_LevelSelTex2;
	Texture* m_PauseScreenBG;
	Texture* m_PauseScreenIcons;
	Texture* m_DeathScreen;
	Texture* m_ResultsScreen;
	Texture* m_LettersForResults;

	bool m_ResetGameplay{false};
	int m_Lives{ 3 };
	int m_Coins{ 0 };
	int m_RedCoins{ 0 };
	int m_Flowers{ 0 };
	int m_Stars{ 0 };
	int m_PointerPosX{ 200 };
};

