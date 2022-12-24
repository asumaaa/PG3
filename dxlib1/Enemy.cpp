#include "Enemy.h"
#include "DxLib.h"
int Enemy::enemyCount;
int Enemy::preEnemyCount;

Enemy::Enemy()
{
	enemyCount++;
	preEnemyCount = enemyCount;
}

void Enemy::Initialize()
{
	//‰ŠúˆÊ’uÝ’è
	pos.x = (float)enemyCount * 70;
	pos.y = 50;
};

void Enemy::Update()
{
	if (preEnemyCount > enemyCount)
	{
		deadFlag = true;
	}

	preEnemyCount = enemyCount;
};

void Enemy::Draw()
{
	DrawCircle(pos.x, pos.y, r, color, false);
};