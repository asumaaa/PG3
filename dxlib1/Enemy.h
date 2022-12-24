#pragma once
#include "DirectXMath.h"

class Enemy
{
public: //静的メンバ変数
	static int enemyCount;
	static int preEnemyCount;
public://メンバ関数
	//コンストラクタ、デストラクタ
	Enemy();
	~Enemy() { enemyCount--; }
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	//ゲッター
	DirectX::XMFLOAT2 GetPosition() { return pos; }
	int GetSize() { return r; }
	bool GetDeadFlag() { return deadFlag; }

	//セッター
	void SetDeadFlag() { deadFlag = true; }

private://メンバ変数
	//座標
	DirectX::XMFLOAT2 pos;
	//半径
	float r = 16;
	//色
	int color = 0xffffff;
	//フラグ
	bool deadFlag = false;
};

