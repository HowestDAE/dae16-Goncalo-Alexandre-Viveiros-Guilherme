#pragma once
#include <vector>
#include "utils.h"


class Texture;
class Yoshi;
class UI final
{
public:
	UI(const std::string& texturePath, float txtHeight, float txtWidth);
	~UI();
	UI(const UI& rhs) = delete;
	UI& operator=(const UI& rhs) = delete;
	UI(UI&& rhs) = delete;

	void Draw(Point2f camPos) const;
	void Update(bool isMarioOn, int marioTimer);
	void Reset();

private:
	Texture* m_UITexture;
	std::vector <float> m_TxtHeight;
	std::vector <float>  m_TxtWidth;
	std::vector <float>  m_XTxtPos ;
	std::vector <float>  m_YTxtPos ;
	
	int m_Number{10};
	int m_FirstDigit{1};
	int m_SecondDigit{0};
};

