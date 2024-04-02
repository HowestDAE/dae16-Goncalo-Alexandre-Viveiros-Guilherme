#pragma once
#include <vector>

class Texture;
class Entity
{
public:
	Entity(const std::string& TexturePath, float txtHeight, float txtWidth, Point2f position);
	~Entity();
	void Draw() const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);

private:
	Texture* m_EntityTxt;
	bool m_IsFacingRight{ true };
	bool m_IsGrounded{ false };

protected:
	Point2f m_Position;
	const float m_TxtHeight;
	const float m_TxtWidth;
	float m_VelocityY{ 0 };
	float m_VelocityX{ 0 };
	float xTxtPos{ 0 };
	float yTxtPos{ 0 };
};

