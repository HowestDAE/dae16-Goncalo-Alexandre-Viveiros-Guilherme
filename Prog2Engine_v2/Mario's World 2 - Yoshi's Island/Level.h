#pragma once
#include <vector>

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
	void DrawLvl() const;
	void DrawOthers() const;
	void DrawBackground() const;
	void Update(float elapsedSec, bool isPlayerPauseTrue);
	void Animate(float elapsedSec);
	void WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, float pipeWidth, float pipeHeight, Point2f pipeWarpDestination, Camera* &plyrCamera);
	void LevelEndUpdate(Point2f yoshiPos);
	float GetLevelStart() const;
	bool GetLevelPause() const;
	Point2f GetLevelEnd() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices() const;
	std::vector<WingedClouds*>& GetWingedClouds();
	std::vector<Flower*>& GetFlowers();

private:
	bool m_LevelPause{ false };
	bool m_DrawEventStairs{ false };
	bool m_DrawEventSunflower{ false };
	int m_LevelNumber{0};
	float m_LevelStart;
	Point2f m_LevelEnd;
	float m_BgFrameStart{8};
	float m_BgFrameWidht{512};
	float m_BgFrameHeight{1024};
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
	Texture* m_BgTexture2;
	Texture* m_BgTexture3;
	std::vector< std::vector<Point2f>> m_LvlVertices{};
	std::vector<Platforms*> m_Platforms;
	std::vector<WingedClouds*> m_WingedClouds {};
	std::vector<Flower*> m_Flowers{};
	Texture* m_StairCloudTxt;
	Texture* m_SunflowerCloudTxt;
};

