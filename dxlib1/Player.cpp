#include "Player.h"
#include "DxLib.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Update(char key[],char oldKey[])
{
	//ASDW�ňړ�
	pos.x -= key[KEY_INPUT_A] * 2;
	pos.x += key[KEY_INPUT_D] * 2;
	pos.y -= key[KEY_INPUT_W] * 2;
	pos.y += key[KEY_INPUT_S] * 2;

	//�X�y�[�X�Œe�t���O�𗧂Ă�
	shotFlag = key[KEY_INPUT_SPACE] && !oldKey[KEY_INPUT_SPACE];
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, r, color, true);
}
