#pragma once
#include "DirectXMath.h"

class Enemy
{
public: //�ÓI�����o�ϐ�
	static int enemyCount;
	static int preEnemyCount;
public://�����o�֐�
	//�R���X�g���N�^�A�f�X�g���N�^
	Enemy();
	~Enemy() { enemyCount--; }
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�Q�b�^�[
	DirectX::XMFLOAT2 GetPosition() { return pos; }
	int GetSize() { return r; }
	bool GetDeadFlag() { return deadFlag; }

	//�Z�b�^�[
	void SetDeadFlag() { deadFlag = true; }

private://�����o�ϐ�
	//���W
	DirectX::XMFLOAT2 pos;
	//���a
	float r = 16;
	//�F
	int color = 0xffffff;
	//�t���O
	bool deadFlag = false;
};

