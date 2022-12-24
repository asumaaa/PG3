#pragma once
#include "DirectXMath.h"

class Player
{
public://メンバ関数
	//コンストラクタ、デストラクタ
	Player();
	~Player();
	//初期化
	void Initialize();
	//更新
	void Update(char key[], char oldKey[]);
	//描画
	void Draw();

	//セッター
	void SetPosition(DirectX::XMFLOAT2 pos) { Player::pos = pos; }

	//ゲッター
	bool GetShotFlag() { return shotFlag; }
	DirectX::XMFLOAT2 GetPosition() { return pos; }

private://メンバ変数
	//座標
	DirectX::XMFLOAT2 pos;
	//半径
	float r = 24;
	//色
	int color = 0xffffff;

	//弾発射のフラグ
	bool shotFlag = false;
};

