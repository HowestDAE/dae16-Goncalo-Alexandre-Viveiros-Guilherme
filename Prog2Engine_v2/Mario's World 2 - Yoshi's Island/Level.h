#pragma once
#include <vector>

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
	void Update(float elapsedSec) const;
	void Animate(float elapsedSec);
	void WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, float pipeWidth, float pipeHeight, Point2f pipeWarpDestination, Camera* &plyrCamera);
	void LevelEndUpdate(Point2f yoshiPos);
	float GetLevelStart() const;
	Point2f GetLevelEnd() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices() const;
	std::vector<WingedClouds*>& GetWingedClouds();

private:
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
};

