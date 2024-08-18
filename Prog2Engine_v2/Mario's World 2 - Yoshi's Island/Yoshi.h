#pragma once
#include <vector>
#include "Entity.h"
#include "UI.h"

class SoundManager;
class Boulder;
class Flower;
class WingedClouds;
class Egg;
class Enemy;
class Texture;
class Yoshi final : public Entity
{
public:
	explicit Yoshi(Point2f startPos);
	~Yoshi() override;

	void Draw()const override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, const std::vector< std::vector<Point2f>>& movingPlatforms, SoundManager* soundManager,float elapsedSec);
	void Collision(const std::vector< std::vector<Point2f>>& platforms, const std::vector< std::vector<Point2f>>& movingPlatforms, float elapsedSec);
	void Sound(SoundManager* soundManager);
	void KeysDown();
	void KeysUp(const SDL_KeyboardEvent& e);
	void Debug();
	void HitCheck(const std::vector<Enemy*>, std::vector<Entity*> lvlEntities, Rectf marioHitbox, SoundManager* soundManager);
	void EmptyMouth();
	void AddFlower();
	void AddCoin();
	void AddRedCoin();
	int GetMarioTimer() const;
	int GetEggAmount() const;
	int GetStarsAmount() const;
	int GetFlowersAmount() const;
	int GetCoinsAmount() const;
	int GetRedCoinsAmount() const;
	bool GetIsMarioOn() const;
	bool GetIsJumping() const;
	bool GetIsHovering() const;
	bool GetIsCrouching() const;
	bool GetIsLookingUp() const;
	bool GetIsEnemySpatOut()const;
	bool GetIsOnMovingPlatform() const;
	bool GetIsHit() const;
	bool GetIsUsingPipe() const;
	void FlipIsUsingPipe();
	void Reset() override;


private:
	bool m_IsTonguing{ false };
	bool m_IsYoshiJumping{false};
	bool m_IsMarioOn;
	bool m_IsLookingUp{ false };
	bool m_IsHit{ false };
	bool m_IsEnemySpitOut{ false };
	bool m_IsUsingPipe{false};
	int m_Flowers{ 0 };
	int m_Coins{ 0 };
	int m_RedCoins{ 0 };
	int m_Stars{ 0 };
	int m_MarioTimer;
	float m_FlightTime{ 0 };
	float m_Countdown{ 0 };
	float m_HitTimer{ 0 };
	float m_HitPhases{ 0 };
	float m_JumpTimer{0};
	float m_PushTimer{ 0 };
	float m_ControlsTimer{ 0 };
	Circlef m_Tongue;
	bool m_IsMouthFull{false};
	std::vector <Egg*> m_Eggs;
	Point2f m_FeetPos;
	bool m_CanYoshiJump{ true };
	bool m_IsJumpDone{ false };
	bool m_IsHoldingEgg{ false };
	bool m_IsCalculatingAngle{ true };
	bool m_IsCrouching{ false };
	bool m_IsLayingEgg{ false };
	bool m_IsOnMovingPlatform{ false };
	bool m_IsPushing{ false };
	bool m_IsTongueReady{ true };
	bool m_IsStandingOnEntity{ false };
	


	bool m_PlayJumpSFX{ false };
	bool m_PlayTongueSFX{ false };

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


	void Animate(float elapsedSec) override;
};

