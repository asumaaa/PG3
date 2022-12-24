#pragma once
#include "DirectXMath.h"

class PlayerBullet
{
public:
	//コンストラクタ、デストラクタ
	PlayerBullet();
	~PlayerBullet();
	//初期化
	void Initialize(DirectX::XMFLOAT2 pos);
	void Update();
	void Draw();

	//ゲッター
	bool GetDeadFlag() { return deadFlag; }
	DirectX::XMFLOAT2 GetPosition() { return pos; }
	int GetSize() { return r; }
	
private:
	//座標
	DirectX::XMFLOAT2 pos;
	//弾の移動ベクトル
	DirectX::XMFLOAT2 velocity = {0,-5};
	//半径
	int r = 8;
	//色
	int color = 0xffffff;
	//弾を消すフラグ
	bool deadFlag = false;
	bool deadTimer;
	bool deadTime;
};

