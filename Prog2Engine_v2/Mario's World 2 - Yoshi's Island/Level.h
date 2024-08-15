#pragma once
#include <vector>

#include "StateManager.h"

class StateManager;
class Coin;
class SoundManager;
class Entity;
class Enemy;
class Boulder;
class Flower;
class WingedClouds;
class Camera;
class Yoshi;
class Platforms;
class Texture;
class Level
{
public:
	Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt2,
		const std::string& backgroundTxt3,float levelStart,Point2f levelEnd, int levelNumber, StateManager* & stateManager);
	~Level();
	Level(const Level& rhs) = delete;
	Level& operator=(const Level& rhs) = delete;
	Level(Level&& rhs) = delete;


	void DrawLvl(Point2f camPos) const;
	void DrawOthers() const;
	void DrawBackground() const;
	void Update(float elapsedSec,Yoshi*& yoshiPlyr, const std::vector<Enemy*>& enemies, SoundManager*& soundManager, Camera*& plyrCamera);
	void Sound(SoundManager* &soundManager);
	void PauseMusic(SoundManager*& soundManager);
	void CoinManager(int coinRowSize,int coinColumnSize,int numberOfRedCoin, int spacingX, int spacingY, Point2f position);
	void WarpPipesCheck(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, int pipeWidth, int pipeHeight, Point2f pipeWarpDestination);
	void WarpPipesUpdate(bool isDownPipe, Yoshi*& yoshiPlyr, Point2f pipeWarpDestination, Camera*& plyrCamera, float elapsedSec);
	void LevelEndUpdate(Point2f yoshiPos);
	float GetLevelStart() const;
	Point2f GetLevelEnd() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices() const;
	std::vector<Entity*>& GetLevelEntities();
	void Reset();

private:
	bool m_DrawEventStairs{ false };
	bool m_DrawEventSunflower{ false };
	bool m_IsBGMusicOn{ false };
	int m_LevelNumber{0};
	float m_LevelStart;
	bool m_IsUsingPipe{ false };
	float m_PipeTiming{ 0 };
	int m_PipeNumber{ 0 };
	bool m_IsActivePipeDirectionDown;
	Point2f m_ActivePipeDestinationPos;
	Point2f m_LevelEnd;
	float m_BgFrameStart{8};
	float m_BgFrameWidth{512};
	float m_BgFrameHeight{1024};
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
	Texture* m_BgTexture2;
	Texture* m_BgTexture3;
	std::vector<Point2f> m_EventVertices1 {};
	std::vector<Point2f> m_EventVertices2 {};
	std::vector< std::vector<Point2f>> m_LvlVertices{};
	std::vector<Platforms*> m_Platforms;
	std::vector<Entity*> m_LvlEntities;
	Texture* m_StairCloudTxt;
	Texture* m_SunflowerCloudTxt;
	StateManager* m_StateManager;
	StateManager::States m_PreviousState;

	void Animate(float elapsedSec) const;
};

