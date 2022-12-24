#include "PlayerBullet.h"
#include "DxLib.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize(DirectX::XMFLOAT2 pos)
{
	PlayerBullet::pos = pos;
	deadTimer = 0;
	deadTime = 500;
}

void PlayerBullet::Update()
{
	//À•WˆÚ“®
	pos.x += velocity.x;
	pos.y += velocity.y;

	deadTimer++;
	if (deadTimer > deadTime)
	{
		deadFlag = true;
	}
}

void PlayerBullet::Draw()
{
	DrawCircle(pos.x, pos.y, r, color, true);
}
