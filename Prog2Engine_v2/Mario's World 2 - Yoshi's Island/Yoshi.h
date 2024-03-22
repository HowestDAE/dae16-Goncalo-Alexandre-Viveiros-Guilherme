#pragma once
#include <vector>


class Texture;
class Yoshi
{
public:
	Yoshi(Point2f startpos);
	~Yoshi();

	void Draw() const;
	void Animation(float elapsedSec);
	void Update(const std::vector< std::vector<Point2f>>& platforms);

	float m_VelocityY;
	float m_VelocityX;
	Point2f m_Position;
private:
	bool m_IsMarioOn;
	bool m_IsFacingRight{true};
	int m_MarioTimer;
	Texture* m_YoshiTxt;
	
	const float m_StdTxtHeight{ 32 };
	const float m_StdTxtWidth{ 30 };
	float xTxtPos{ 0 };
	float yTxtPos{ 0 };
	float m_FrameTime{0};
	

	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
	};

	AnimState currentState{};
};

