#pragma once
#include <vector>
#include "utils.h"

class Texture;
class Entity
{
public:
	Entity(const std::string& texturePath, float txtHeight, float txtWidth, Point2f position);
	virtual ~Entity();
	Entity(const Entity& rhs) = delete;
	Entity& operator=(const Entity& rhs) = delete;
	Entity(Entity&& rhs) = delete;
	Entity& operator=(Entity&& rhs) = delete;

	virtual void Draw() const;
	virtual void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	virtual void Collision(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	virtual void Animate(float elapsedSec);
	virtual void FlipIsActive();
	void SetPosition(Point2f newPosition);
	void SetVelocity(float velocityX, float velocityY);
	void AddVelocity(float velocityX,float velocityY);
	Rectf GetHitBox() const;
	Point2f GetPosition() const;
	bool GetIsFacingRight() const;
	bool GetIsGrounded() const;
	bool GetIsActive() const;
	Point2f GetVelocity() const;
	virtual void Reset();
	

protected:
	Texture* m_EntityTxt;
	Point2f m_Position;
	Point2f m_ResetPosition;
	float m_TxtHeight;
	float m_TxtWidth;
	float m_VelocityY{ 0 };
	float m_VelocityX{ 0 };
	float m_XTxtPos{ 0 };
	float m_YTxtPos{ 0 };
	bool m_IsGrounded{ false };
	bool m_IsFacingRight{ true };
	bool m_IsActive{ true };
	float m_FrameTime{ 0 };
	float m_TerminalVelocityTimer{ 0 };
	Rectf m_Hitbox{ 0, 0, 0, 0 };

	float m_AngleDeg{0};
	float m_AngX {0};
	float m_AngY {0};
	float m_AngZ {0};
	float m_ScaleX{1};
	float m_ScaleY{1};
	float m_ScaleZ{1};
};

