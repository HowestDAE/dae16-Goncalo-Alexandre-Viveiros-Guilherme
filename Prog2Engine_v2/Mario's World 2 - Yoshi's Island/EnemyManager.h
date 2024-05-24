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
	void AddEnemy(Point2f yoshiPos, bool isYoshiRight);

private:
	std::vector< ShyGuy*> m_ShyGuy;
	std::vector<PiranhaPlant*> m_PiranhaPlant;
	std::vector<WalkingTulip*> m_WalkingTulip;
	std::vector<PogoShyGuy*> m_PogoShyGuy;
	std::vector<FlyingShyGuy*>	 m_FlyingShyGuy;
	std::vector<Enemy*> m_Enemies;
};

