#pragma once


class Texture;
class Yoshi
{
public:
	Yoshi(Point2f startpos);
	~Yoshi();

	void Draw() ;
	void Animation(float elapsedSec);
	void Update();

	

private:
	bool m_IsMarioOn;
	int m_MarioTimer;
	Texture* m_YoshiTxt;
	Point2f m_Position;
	const float m_StdTxtHeight{ 32 };
	const float m_StdTxtWidth{ 30 };
	float xTxtPos{ 0 };
	float yTxtPos{ 0 };


	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
	};


};

