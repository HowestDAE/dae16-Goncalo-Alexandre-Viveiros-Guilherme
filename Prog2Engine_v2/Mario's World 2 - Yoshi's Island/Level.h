#pragma once
#include <vector>

class Camera;
class Yoshi;
class Platforms;
class Texture;
class Level
{
public:
	Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3,float levelStart,float levelEnd);
	~Level();
	void DrawLvl() const;
	void DrawPlatforms() const;
	void DrawBackground() const;
	void Update(float elapsedSec) const;
	void WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, float pipeWidth, float pipeHeight, Point2f pipeWarpDestination, Camera* &plyrCamera);
	float GetLevelStart() const;
	float GetLevelEnd() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices() const;
private:
	float m_LevelStart;
	float m_LevelEnd;
	float m_BgFrameStart{8};
	float m_BgFrameWidht{512};
	float m_BgFrameHeight{1024};
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
	Texture* m_BgTexture2;
	Texture* m_BgTexture3;
	std::vector< std::vector<Point2f>> m_LvlVertices{};
	Platforms* m_Platforms;
};

