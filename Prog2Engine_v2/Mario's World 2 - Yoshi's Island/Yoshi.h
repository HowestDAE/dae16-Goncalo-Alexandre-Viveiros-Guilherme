#pragma once
#include <vector>
#include "Entity.h"

class Egg;
class Enemy;
class Texture;
class Yoshi : public Entity
{
public:
	Yoshi(Point2f startPos);
	~Yoshi();

	void Draw()const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);
	void KeysDown(const SDL_KeyboardEvent& e);
	void KeysUp(const SDL_KeyboardEvent& e);
	void Debug();
	bool GetIsMarioOn() const;
	void HitCheck(std::vector<Enemy*>&);
	

private:
	bool m_IsTonguing;
	bool m_IsYoshiJumping{false};
	bool m_IsMarioOn;
	bool m_IsLookingUp{ false };
	int m_MarioTimer ;
	float m_FrameTime{0};
	float m_FlightTime{ 0 };
	float m_Countdown{ 0 };
	Circlef m_Tongue;
	bool m_IsMouthFull{false};
	std::vector <Egg*> m_Eggs;
	Point2f m_FeetPos;
	bool m_IsJumpDone{ false };

	enum class AnimState {
		Idle,
		Walking,
		Sprinting,
		Jumping,
		Hovering,
		Pushing,
		Tongue,
		FullIdle,
		FullWalking,
		FullSprinting
	};

	AnimState currentState{};
	AnimState lastState{};
};

