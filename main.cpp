#include <stdio.h>
#include <list>
#include <memory>

//�I�^�N�N���X
class Otaku
{
public://�����o�֐�
	//�U��
	virtual void Attack();
};

//���ʂ̃I�^�N�N���X
class NormalOtaku : public Otaku
{
public://�����o�֐�
	//�U��
	void Attack() override;
};

//�C�L���I�^�N�N���X
class IkiriOtaku : public Otaku
{
public://�����o�֐�
	//�U��
	void Attack() override;
};

//�A�L���I�^�N�N���X
class InkyaOtaku : public Otaku
{
public://�����o�֐�
	//�U��
	void Attack() override;
};

int main()
{
	//�I�^�N
	std::list<std::unique_ptr<Otaku>>otakus;

	//1�l�ڂ𕁒ʂ̃I�^�N�ɂ���
	{
		std::unique_ptr<NormalOtaku> newOtaku = std::make_unique<NormalOtaku>();
		otakus.push_back(std::move(newOtaku));
	}
	//2�l�ڂ��C�L���I�^�N�ɂ���
	{
		std::unique_ptr<IkiriOtaku> newOtaku = std::make_unique<IkiriOtaku>();
		otakus.push_back(std::move(newOtaku));
	}
	//3�l�ڂ��A�L���I�^�N�ɂ���
	{
		std::unique_ptr<InkyaOtaku> newOtaku = std::make_unique<InkyaOtaku>();
		otakus.push_back(std::move(newOtaku));
	}

	//�I�^�N�B���U������
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
	printf("���ʂ̃I�^�N���`�㑁���A�^�b�N\n");
}

void IkiriOtaku::Attack()
{
	printf("�C�L���I�^�N�̃j�`���j�`���A�^�b�N\n");
}

void InkyaOtaku::Attack()
{
	printf("�A�L���I�^�N�͉��Q�[�����Ă���\n");
}
