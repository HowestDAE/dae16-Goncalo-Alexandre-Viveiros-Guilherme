#pragma once
#include <vector>
#include "utils.h"

class Texture;
class Entity
{
public:
	Entity(const std::string& texturePath, float txtHeight, float txtWidth, Point2f position);
	virtual ~Entity();
	virtual void Draw() const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void SetPosition(Point2f newPosition);
	Rectf GetHitBox() const;
	Point2f GetPosition() const;
	bool GetIsFacingRight() const;
	bool GetIsGrounded() const;
	Point2f GetVelocity() const;

protected:
	Texture* m_EntityTxt;
	Point2f m_Position;
	float m_TxtHeight;
	float m_TxtWidth;
	float m_VelocityY{ 0 };
	float m_VelocityX{ 0 };
	float m_XTxtPos{ 0 };
	float m_YTxtPos{ 0 };
	bool m_IsGrounded{ false };
	bool m_IsFacingRight{ true };
	float m_FrameTime{ 0 };
	float m_TerminalVlcityTimer{ 0 };
	Rectf m_Hitbox{ 0, 0, 0, 0 };

	float m_AngleDeg{0};
	float m_AngX {0};
	float m_AngY {0};
	float m_AngZ {0};
	float m_ScaleX{1};
	float m_ScaleY{1};
	float m_ScaleZ{1};
};

