#pragma once
#include "DirectXMath.h"

class PlayerBullet
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	PlayerBullet();
	~PlayerBullet();
	//������
	void Initialize(DirectX::XMFLOAT2 pos);
	void Update();
	void Draw();

	//�Q�b�^�[
	bool GetDeadFlag() { return deadFlag; }
	DirectX::XMFLOAT2 GetPosition() { return pos; }
	int GetSize() { return r; }
	
private:
	//���W
	DirectX::XMFLOAT2 pos;
	//�e�̈ړ��x�N�g��
	DirectX::XMFLOAT2 velocity = {0,-5};
	//���a
	int r = 8;
	//�F
	int color = 0xffffff;
	//�e�������t���O
	bool deadFlag = false;
	bool deadTimer;
	bool deadTime;
};

