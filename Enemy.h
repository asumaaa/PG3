#pragma once
class Enemy
{
public:
	static int EnemyCount;
	Enemy() { EnemyCount++; };
	~Enemy() { EnemyCount--; };
	void Update();
	void Dead() { deathFlag = true; };
	bool GetDeathFlag() { return deathFlag; };
private:
	bool deathFlag = false;
};

