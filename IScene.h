#pragma once

//�V�[���̊��N���X
class IScene
{
public:
	IScene() {};
	~IScene() {};
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual int GetInputNum() = 0;
};