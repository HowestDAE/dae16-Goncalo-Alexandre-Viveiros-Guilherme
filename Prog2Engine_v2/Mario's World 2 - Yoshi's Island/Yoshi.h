#pragma once
#include <vector>
#include "Entity.h"

class Flower;
class WingedClouds;
class Egg;
class Enemy;
class Texture;
class Yoshi : public Entity
{
public:
	Yoshi(Point2f startPos);
	virtual ~Yoshi() override;

	void Draw()const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, const std::vector< std::vector<Point2f>>& movingPlatforms,float elapsedSec);
	void Animate(float elapsedSec);
	void KeysDown();
	void KeysUp(const SDL_KeyboardEvent& e);
	void Debug();
	bool GetIsMarioOn() const;
	bool GetIsJumping() const;
	bool GetIsHovering() const;
	bool GetIsCrouching() const;
	bool GetPlayerPause() const;
	bool GetIsOnMovingPlatform() const;
	void HitCheck(std::vector<Enemy*>&, const std::vector<WingedClouds*> &wingedClouds, Rectf marioHitbox, std::vector<Flower*>& flowers);
	

private:
	bool m_IsTonguing{ false };
	bool m_IsYoshiJumping{false};
	bool m_IsMarioOn;
	bool m_IsLookingUp{ false };
	bool m_IsHit{ false };
	int m_MarioTimer ;
	int m_Flowers{ 0 };
	float m_FlightTime{ 0 };
	float m_Countdown{ 0 };
	float m_HitTimer{ 0 };
	float m_JumpTimer{0};
	Circlef m_Tongue;
	bool m_IsMouthFull{false};
	std::vector <Egg*> m_Eggs;
	Point2f m_FeetPos;
	bool m_IsJumpDone{ false };
	bool m_IsHoldingEgg{ false };
	bool m_IsCalculatingAngle{ true };
	bool m_IsCrouching{ false };
	bool m_IsLayingEgg{ false };
	bool m_PlayerPause{ false };
	bool m_IsOnMovingPlatform{ false };

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
		FullSprinting,
		LayingEgg,
		AimIdle,
		AimWalking,
		AimFluttering
	};

	AnimState m_CurrentState{};
	AnimState m_LastState{};
};

