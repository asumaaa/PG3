#pragma once
#include "IScene.h"

class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};
	void update() override;
	void draw() override;
	int GetInputNum()override { return inputNum; }
private:
	int inputNum;
};

void GameScene::update()
{
	int n = 0;
	scanf_s("%d", &n);
	inputNum = n;
}

void GameScene::draw()
{
	printf("���݂̓Q�[���ł�\n");
	printf("���l����͂��Ă�������\n");
	printf("1:�^�C�g����\n");
	printf("2:�Q�[����\n");
	printf("3:�Q�[���I�[�o�[��\n");
	printf("4:�N���A��\n");
	printf("5:�I��\n");
}