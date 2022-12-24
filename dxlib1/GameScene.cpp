#include "GameScene.h"
#include "DxLib.h"
#include <cmath>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	//プレイヤー初期化
	Player* newPlayer = new Player();
	newPlayer->Initialize();
	player.reset(newPlayer);
	player->SetPosition({100, 500});

	//敵初期化
	for (int i = 0; i < enemyCount; i++)
	{
		std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize();
		enemys.push_back(std::move(newEnemy));
	}
}

void GameScene::Update()
{
	//キーボード更新
	GetHitKeyStateAll(key);

	//当たり判定更新
	CheckCollision();

	//プレイヤー更新
	player->Update(key,oldKey);

	//プレイヤーからフラグを受け取り弾生成
	if (player->GetShotFlag())
	{
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(player->GetPosition());
		playerBullets.push_back(std::move(newBullet));
	}

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		bullet->Update();
	}

	//フラグの立った弾を削除
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->GetDeadFlag(); });

	//敵更新
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update();
	}

	//フラグの立った敵を削除
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->GetDeadFlag(); });

	//oldkeyを取得
	memcpy(oldKey, key, sizeof(key));
}

void GameScene::Draw()
{
	player->Draw();

	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		bullet->Draw();
	}

	//敵描画
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw();
	}

	//文字
	DrawFormatString(0, 530, 0xffffff, "ASDW:移動");
	DrawFormatString(0, 550, 0xffffff, "SPACE:弾");
}

void GameScene::CheckCollision()
{
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			//変数を用意
			float x = std::pow(bullet->GetPosition().x - enemy->GetPosition().x, 2);
			float y = std::pow(bullet->GetPosition().y - enemy->GetPosition().y, 2);
			float r = std::pow(bullet->GetSize() + enemy->GetSize(), 2);

			//当たっていたらフラグを立てる
			if (x + y <= r)
			{
				enemy->SetDeadFlag();
			}
		}
	}
}
