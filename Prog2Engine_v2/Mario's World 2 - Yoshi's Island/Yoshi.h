#pragma once
#include <vector>
#include "Entity.h"


class Texture;
class Yoshi : public Entity
{
public:
	Yoshi(Point2f startPos);
	~Yoshi();

	void Animation(float elapsedSec);
	void Controls(const SDL_KeyboardEvent& e);
	Point2f GetYoshiPos() const;
	void Debug();
	bool GetIsGrounded() const;
	bool GetIsFacingRight() const;
	
private:
	bool m_IsMarioOn;
	bool m_IsYoshiGrounded{ true };
	int m_MarioTimer ;
	float m_FrameTime{0};
	float lastYPos;
	float lastXPos;
	

	

	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
		Pushing,
	};

	AnimState currentState{};
};

