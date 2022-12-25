#pragma once
#include "IScene.h"

class ClearScene : public IScene
{
public:
	ClearScene(){};
	~ClearScene(){};
	void update() override;
	void draw() override;
	int GetInputNum() override { return inputNum; }
private:
	int inputNum;
};

void ClearScene::update()
{
	int n = 0;
	scanf_s("%d", &n);
	inputNum = n;
}

void ClearScene::draw()
{
	printf("現在はクリアです\n");
	printf("数値を入力してください\n");
	printf("1:タイトルへ\n");
	printf("2:ゲームへ\n");
	printf("3:ゲームオーバーへ\n");
	printf("4:クリアへ\n");
	printf("5:終了\n");
}