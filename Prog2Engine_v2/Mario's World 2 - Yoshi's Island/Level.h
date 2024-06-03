#pragma once
#include <vector>

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
	Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3,float levelStart,Point2f levelEnd, int levelNumber);
	~Level();
	Level(const Level& rhs) = delete;
	Level& operator=(const Level& rhs) = delete;
	Level(Level&& rhs) = delete;


	void DrawLvl(Point2f camPos) const;
	void DrawOthers() const;
	void DrawBackground() const;
	void Update(float elapsedSec, bool isPlayerPauseTrue, Yoshi*& yoshiPlyr, const std::vector<Enemy*>& enemies, SoundManager*& soundManager);
	void Sound(SoundManager* &soundManager);
	void CoinManager(int coinRowSize,int coinColumnSize,int numberOfRedCoin,int spacing, Point2f position);
	static void WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, int pipeWidth, int pipeHeight, Point2f pipeWarpDestination, Camera* &plyrCamera);
	void LevelEndUpdate(Point2f yoshiPos);
	float GetLevelStart() const;
	bool GetLevelPause() const;
	Point2f GetLevelEnd() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices() const;
	std::vector<Entity*>& GetLevelEntities();


private:
	bool m_LevelPause{ false };
	bool m_DrawEventStairs{ false };
	bool m_DrawEventSunflower{ false };
	bool m_IsBGMusicOn{ false };
	int m_LevelNumber{0};
	float m_LevelStart;
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

	void Animate(float elapsedSec) const;
};

