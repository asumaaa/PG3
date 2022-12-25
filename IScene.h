#pragma once

//シーンの基底クラス
class IScene
{
public:
	IScene() {};
	~IScene() {};
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual int GetInputNum() = 0;
};