#pragma once
#include "DirectXMath.h"

class Player
{
public://�����o�֐�
	//�R���X�g���N�^�A�f�X�g���N�^
	Player();
	~Player();
	//������
	void Initialize();
	//�X�V
	void Update(char key[], char oldKey[]);
	//�`��
	void Draw();

	//�Z�b�^�[
	void SetPosition(DirectX::XMFLOAT2 pos) { Player::pos = pos; }

	//�Q�b�^�[
	bool GetShotFlag() { return shotFlag; }
	DirectX::XMFLOAT2 GetPosition() { return pos; }

private://�����o�ϐ�
	//���W
	DirectX::XMFLOAT2 pos;
	//���a
	float r = 24;
	//�F
	int color = 0xffffff;

	//�e���˂̃t���O
	bool shotFlag = false;
};

