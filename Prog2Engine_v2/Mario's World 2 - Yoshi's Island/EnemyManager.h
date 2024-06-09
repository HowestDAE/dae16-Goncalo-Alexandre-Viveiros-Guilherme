#pragma once
#include <vector>
class Mario;
class SoundManager;
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
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec,Yoshi*& yoshiplyr, std::vector<Entity*>& lvlEntities, SoundManager*& soundManager, Mario*& babyMarioPointer);
	void SpawnEnemies(int levelNumber);
	void SpawnZone(int yoshiEggAmount, Point2f yoshiPos, float elapsedSec,Point2f spawnZoneLocation);
	std::vector<Enemy*>& GetEnemyVector();
	void AddEnemy(Point2f yoshiPos, bool isYoshiFacingRight);

private:
	std::vector<Enemy*> m_Enemies;
	float m_SpawnTimer {0};
	int m_LevelNumber;

};

