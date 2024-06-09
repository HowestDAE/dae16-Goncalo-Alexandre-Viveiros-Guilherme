#pragma once
class StateManager
{
	enum class States
	{
		Intro,
		StartMenu,
		LevelSelector,
		Gameplay,
		PlayerPause,
		ResultsMenu,
		BonusLevels
	};

	StateManager();
	~StateManager();
};

