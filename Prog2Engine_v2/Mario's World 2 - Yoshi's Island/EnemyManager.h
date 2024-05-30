#pragma once
#include <vector>
class Entity;
class Yoshi;
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
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec,Yoshi*& yoshiplyr, std::vector<Entity*>& lvlEntities);
	void SpawnEnemies(int levelNumber);
	std::vector<Enemy*>& GetEnemyVector();
	void AddEnemy(Point2f yoshiPos, bool isYoshiFacingRight);

private:
	std::vector<Enemy*> m_Enemies;
};

