#pragma once
#include <vector>
class ShyGuy;
class Enemy;

class EnemyManager
{
public:
	EnemyManager(std::vector<Enemy*>& enemies);
	~EnemyManager();
	void Draw() const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	std::vector<Enemy*>& GetEnemyVector();
	void AddEnemy(Point2f yoshiPos, bool isYoshiRight);

private:
	std::vector<Enemy*> m_Enemies;
};

