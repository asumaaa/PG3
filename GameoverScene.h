#pragma once
#include "IScene.h"

class GameoverScene : public IScene
{
public:
	GameoverScene() {};
	~GameoverScene() {};
	void update() override;
	void draw() override;
	int GetInputNum() override { return inputNum; }
private:
	int inputNum;
};

void GameoverScene::update()
{
	int n = 0;
	scanf_s("%d", &n);
	inputNum = n;
}

void GameoverScene::draw()
{
	printf("���݂̓Q�[���I�[�o�[�ł�\n");
	printf("���l����͂��Ă�������\n");
	printf("1:�^�C�g����\n");
	printf("2:�Q�[����\n");
	printf("3:�Q�[���I�[�o�[��\n");
	printf("4:�N���A��\n");
	printf("5:�I��\n");
}