#pragma once
#include <vector>
class PiranhaPlant;
class WalkingTulip;
class PogoShyGuy;
class FlyingShyGuy;
class ShyGuy;
class Enemy;

class EnemyManager
{
public:
	EnemyManager() = default;
	~EnemyManager();
	EnemyManager(const EnemyManager& rhs) = delete;
	EnemyManager& operator=(const EnemyManager& rhs) = delete;
	EnemyManager(EnemyManager&& rhs) = delete;

	void Draw() const;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec, Point2f yoshiPos);
	void SpawnEnemies(int levelNumber);
	std::vector<Enemy*>& GetEnemyVector();
	void AddEnemy(Point2f yoshiPos, bool isYoshiFacingRight);

private:
	std::vector<Enemy*> m_Enemies;
};

