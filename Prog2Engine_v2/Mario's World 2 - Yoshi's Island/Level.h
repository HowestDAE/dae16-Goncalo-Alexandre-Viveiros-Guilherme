#pragma once

class Texture;
class Level
{
public:
	Level(const std::string& imagePath_lvlTxt, const std::string& imagePath_backgroundTxt);
	~Level();
	void DrawLvl() const;
	void DrawBackground() const;
private:
	float m_BgFrameStart{8};
	float m_BgFrameWidht{512};
	float m_BgFrameHeight{1024};
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
};

