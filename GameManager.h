#pragma once
#include <list>
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameoverScene.h"
#include "ClearScene.h"

class GameManager
{
private:
	std::unique_ptr<IScene> currentScene;
public:
	GameManager(){ currentScene = std::make_unique<TitleScene>(); }
	~GameManager(){}
	void run();
};

void GameManager::run()
{
	while (true)
	{
		printf("---------------------------------\n");

		currentScene->draw();
		currentScene->update();

		if (currentScene->GetInputNum() == 1)currentScene = std::make_unique<TitleScene>();
		else if (currentScene->GetInputNum() == 2)currentScene = std::make_unique<GameScene>();
		else if (currentScene->GetInputNum() == 3)currentScene = std::make_unique<GameoverScene>();
		else if (currentScene->GetInputNum() == 4)currentScene = std::make_unique<ClearScene>();
		else if (currentScene->GetInputNum() == 5)break;
		else printf("³‚µ‚­“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");

		printf("\n");
	}
}