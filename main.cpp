#include <stdio.h>
#include <list>
#include <memory>

//オタククラス
class Otaku
{
public://メンバ関数
	//攻撃
	virtual void Attack();
};

//普通のオタククラス
class NormalOtaku : public Otaku
{
public://メンバ関数
	//攻撃
	void Attack() override;
};

//イキリオタククラス
class IkiriOtaku : public Otaku
{
public://メンバ関数
	//攻撃
	void Attack() override;
};

//陰キャオタククラス
class InkyaOtaku : public Otaku
{
public://メンバ関数
	//攻撃
	void Attack() override;
};

int main()
{
	//オタク
	std::list<std::unique_ptr<Otaku>>otakus;

	//1人目を普通のオタクにする
	{
		std::unique_ptr<NormalOtaku> newOtaku = std::make_unique<NormalOtaku>();
		otakus.push_back(std::move(newOtaku));
	}
	//2人目をイキリオタクにする
	{
		std::unique_ptr<IkiriOtaku> newOtaku = std::make_unique<IkiriOtaku>();
		otakus.push_back(std::move(newOtaku));
	}
	//3人目を陰キャオタクにする
	{
		std::unique_ptr<InkyaOtaku> newOtaku = std::make_unique<InkyaOtaku>();
		otakus.push_back(std::move(newOtaku));
	}

	//オタク達が攻撃する
	for (std::unique_ptr<Otaku>& otaku : otakus)
	{
		otaku->Attack();
	}

	return 0;
}

void Otaku::Attack()
{
}

void NormalOtaku::Attack()
{
	printf("普通のオタクの饒舌早口アタック\n");
}

void IkiriOtaku::Attack()
{
	printf("イキリオタクのニチャニチャアタック\n");
}

void InkyaOtaku::Attack()
{
	printf("陰キャオタクは音ゲーをしている\n");
}
