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
	//�R���X�g���N�^�A�f�X�g���N�^
	GameScene();
	~GameScene();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�����蔻��
	void CheckCollision();

private:
	//�L�[�{�[�h���
	char key[256];
	char oldKey[256] = {0};

	//�v���C���[
	std::unique_ptr<Player>player;
	//�v���C���[�̒e
	std::list<std::unique_ptr<PlayerBullet>>playerBullets;

	//�G�̐�
	const int32_t enemyCount = 14;
	//�G
	std::list<std::unique_ptr<Enemy>>enemys;
};

