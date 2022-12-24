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
	//�v���C���[������
	Player* newPlayer = new Player();
	newPlayer->Initialize();
	player.reset(newPlayer);
	player->SetPosition({100, 500});

	//�G������
	for (int i = 0; i < enemyCount; i++)
	{
		std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize();
		enemys.push_back(std::move(newEnemy));
	}
}

void GameScene::Update()
{
	//�L�[�{�[�h�X�V
	GetHitKeyStateAll(key);

	//�����蔻��X�V
	CheckCollision();

	//�v���C���[�X�V
	player->Update(key,oldKey);

	//�v���C���[����t���O���󂯎��e����
	if (player->GetShotFlag())
	{
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(player->GetPosition());
		playerBullets.push_back(std::move(newBullet));
	}

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		bullet->Update();
	}

	//�t���O�̗������e���폜
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->GetDeadFlag(); });

	//�G�X�V
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update();
	}

	//�t���O�̗������G���폜
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->GetDeadFlag(); });

	//oldkey���擾
	memcpy(oldKey, key, sizeof(key));
}

void GameScene::Draw()
{
	player->Draw();

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		bullet->Draw();
	}

	//�G�`��
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw();
	}

	//����
	DrawFormatString(0, 530, 0xffffff, "ASDW:�ړ�");
	DrawFormatString(0, 550, 0xffffff, "SPACE:�e");
}

void GameScene::CheckCollision()
{
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			//�ϐ���p��
			float x = std::pow(bullet->GetPosition().x - enemy->GetPosition().x, 2);
			float y = std::pow(bullet->GetPosition().y - enemy->GetPosition().y, 2);
			float r = std::pow(bullet->GetSize() + enemy->GetSize(), 2);

			//�������Ă�����t���O�𗧂Ă�
			if (x + y <= r)
			{
				enemy->SetDeadFlag();
			}
		}
	}
}
