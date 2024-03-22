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
	Texture* m_LvlTexture;
	Texture* m_BgTexture;
};

