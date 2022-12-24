#pragma once
class Enemy
{
protected:
public:
	Enemy(int x, int y);
	~Enemy() {};
public:
	void Update();
	void Approach();
	void Shot();
	void Leave();
	void SceneManager();
	void Draw();
	void Dead() { deathFlag = true; };
	bool GetDeathFlag() { return deathFlag; };
private:
	int posX, posY;
	int r = 32;
	int preEnemyCount;
	bool deathFlag = false;
	//�V�[���p�̃^�C�}�[
	int sceneTimer = 0;
	//�V�[��
	enum class Scene
	{
		Approach,
		Shot,
		Leave,
	};
	//�V�[��	�ŏ����^�C�g��
	size_t scene = static_cast<size_t>(Scene::Approach);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (Enemy::* Scene[])();
};

