#pragma once
#include <vector>

class Texture;
class Level
{
public:
	Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3);
	~Level();
	void DrawLvl() const;
	void DrawBackground() const;
	std::vector<std::vector<Point2f>> GetLevelVertices();
private:
	float m_BgFrameStart{8};
	float m_BgFrameWidht{512};
	float m_BgFrameHeight{1024};
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
	Texture* m_BgTexture2;
	Texture* m_BgTexture3;
	std::vector< std::vector<Point2f>> m_LvlVertices{};
};

