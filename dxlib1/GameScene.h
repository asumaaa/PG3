#pragma once
#include "Enemy.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "vector"
#include "list"
#include "memory"

class GameScene
{
public:
	//コンストラクタ、デストラクタ
	GameScene();
	~GameScene();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	//当たり判定
	void CheckCollision();

private:
	//キーボード情報
	char key[256];
	char oldKey[256] = {0};

	//プレイヤー
	std::unique_ptr<Player>player;
	//プレイヤーの弾
	std::list<std::unique_ptr<PlayerBullet>>playerBullets;

	//敵の数
	const int32_t enemyCount = 14;
	//敵
	std::list<std::unique_ptr<Enemy>>enemys;
};

