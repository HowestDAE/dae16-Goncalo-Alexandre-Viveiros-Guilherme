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
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Controls(const SDL_KeyboardEvent& e);
	Point2f GetYoshiPos() const;
	
private:
	bool m_IsMarioOn;
	bool m_IsFacingRight{true};
	bool m_IsYoshiGrounded{ true };
	int m_MarioTimer ;
	Texture* m_YoshiTxt;
	float m_VelocityY;
	float m_VelocityX;
	Point2f m_Position;
	const float m_StdTxtHeight{ 32 };
	const float m_StdTxtWidth{ 30 };
	float xTxtPos{ 0 };
	float yTxtPos{ 0 };
	float m_FrameTime{0};
	float m_CurrentTxtWidth;
	

	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
		Pushing,
	};

	AnimState currentState{};
};

