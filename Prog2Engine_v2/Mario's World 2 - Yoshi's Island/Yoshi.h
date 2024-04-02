#pragma once
#include <vector>
#include "Entity.h"


class Texture;
class Yoshi : public Entity
{
public:
	Yoshi(Point2f startpos);
	~Yoshi();

	void Animation(float elapsedSec);
	void Controls(const SDL_KeyboardEvent& e);
	Point2f GetYoshiPos() const;
	
private:
	bool m_IsMarioOn;
	bool m_IsFacingRight{true};
	bool m_IsYoshiGrounded{ true };
	int m_MarioTimer ;
	const float m_StdTxtHeight{ 32 };
	const float m_StdTxtWidth{ 30 };
	float m_FrameTime{0};

	

	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
		Pushing,
	};

	AnimState currentState{};
};

