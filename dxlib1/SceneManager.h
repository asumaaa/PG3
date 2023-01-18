#pragma once

static enum Scene
{
	Title,
	NewGame,
	GamePlay,
	NewClear,
};

class SceneManager final
{
private:
	SceneManager();
	~SceneManager();
public:
	//コピーコンストラクタ無効
	SceneManager(const SceneManager& obj) = delete;
	//代入演算子無効
	SceneManager& operator=(const SceneManager& obj) = delete;
	static SceneManager* GetInstance();
	void ChangeScene(Scene nextScene);
	Scene GetScene() { return scene_; };
	void SetScene(Scene scene) { scene_ = scene; };
private:
	Scene scene_;
};