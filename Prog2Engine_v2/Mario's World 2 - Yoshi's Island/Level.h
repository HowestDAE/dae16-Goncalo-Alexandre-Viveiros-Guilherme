#pragma once
#include <vector>

class Platforms;
class Texture;
class Level
{
public:
	Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3);
	~Level();
	void DrawLvl() const;
	void DrawPlatforms() const;
	void DrawBackground() const;
	void Update(float elapsedSec);
	std::vector<std::vector<Point2f>> GetLevelVertices();
	std::vector<std::vector<Point2f>> GetPlatformVertices();
private:
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

