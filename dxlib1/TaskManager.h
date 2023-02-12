#pragma once
#include "DirectXMath.h"
#include "memory"
#include "list"
#include "string"
#include "vector"

class TaskManager
{
private:
	//�X�V���[�h
	enum class UpdateMode {
		Home,
		Check,
		Edit,
		Member,
	};
	//�`�惂�[�h
	enum class DrawMode {
		Home,
		Check,
		Edit,
		Member,
	};

	//�����o�[��ʂ̍X�V���[�h
	enum class MemberUpdateMode {
		Home,
		Add,
		Delete,
	};
	//�����o�[��ʂ̕`�惂�[�h
	enum class MemberDrawMode {
		Home,
		Add,
		Delete,
	};

	//�`�F�b�N��ʂ̍X�V���[�h
	enum class CheckUpdateMode {
		Home,
		Chack,
	};
	//�`�F�b�N��ʂ̕`�惂�[�h
	enum class CheckDrawMode {
		Home,
		Chack,
	};

	//�ҏW��ʂ̍X�V���[�h
	enum class EditUpdateMode {
		Home,
		Delete,
		Add,
		Edit,
	};
	//�ҏW��ʂ̕`�惂�[�h
	enum class EditDrawMode {
		Home,
		Delete,
		Add,
		Edit,
	};

	//�����o�[
	struct Member
	{
		std::string id;	//ID
		std::string name;	//���O
		std::string className;	//�������Ă���N���X
		//�R���X�g���N�^
		Member(std::string id, std::string name, std::string className)
		{
			this->id = id;
			this->name = name;
			this->className = className;
		};
	};

	//�^�X�N
	struct Task
	{
		std::string id;	//ID
		std::string manager;	//�S����
		std::string name;	//���O
		std::string content;	//���e
		std::string priority;	//�D��x
		std::string state;	//�X�e�[�^�X

		//�R���X�g���N�^
		Task(std::string id, std::string manager, std::string name,
			std::string content, std::string priority, std::string state)
		{
			this->id = id;
			this->manager = manager;
			this->name = name;
			this->content = content;
			this->priority = priority;
			this->state = state;
		};
	};

private:
	TaskManager(){};
	~TaskManager(){};
public:	//�����o�֐�
	//�V���O���g���C���X�^���X���擾
	static TaskManager*GetInstance();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

private://�����o�֐�
	//�e���[�h���Ƃ̍X�V
	void HomeUpdate();
	void CheckUpdate();
	void EditUpdate();
	void MenberUpdate();

	//�e���[�h���Ƃ̕`��
	void HomeDraw();
	void CheckDraw();
	void EditDraw();
	void MenberDraw();

	//�����o�[��ʂ̍X�V
	void MemberHomeUpdate();
	void MemberAddUpdate();
	void MemberDeleteUpdate();

	//�����o�[��ʂ̕`��
	void MemberHomeDraw();
	void MemberAddDraw();
	void MemberDeleteDraw();

	//�`�F�b�N��ʂ̍X�V
	void CheckHomeUpdate();
	void CheckCheckUpdate();

	//�`�F�b�N��ʂ̍X�V
	void CheckHomeDraw();
	void CheckCheckDraw();

	//�ҏW��ʂ̍X�V
	void EditHomeUpdate();
	void EditDeleteUpdate();
	void EditAddUpdate();
	void EditEditUpdate();

	//�ҏW��ʂ̕`��
	void EditHomeDraw();
	void EditDeleteDraw();
	void EditAddDraw();
	void EditEditDraw();

	//�e���[�h�Ɉړ�����ۂɌĂԊ֐�
	void SetHome();
	void SetMemberHome();
	void SetMemberAdd();
	void SetMemberDelete();
	void SetCheckHome();
	void SetCheckCheck();
	void SetEditHome();
	void SetEditDelete();
	void SetEditAdd();
	void SetEditEdit();

private:
	//�X�V���[�h	�ŏ����z�[��
	size_t updateMode = static_cast<size_t>(UpdateMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* UpdateMode[])();

	//�`�惂�[�h	�ŏ����z�[��
	size_t drawMode = static_cast<size_t>(DrawMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* DrawMode[])();

	//�����o�[��ʂ̍X�V���[�h	�ŏ����z�[��
	size_t memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* MemberUpdateMode[])();

	//�����o�[��ʂ̕`�惂�[�h	�ŏ����z�[��
	size_t memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* MemberDrawMode[])();

	//�`�F�b�N��ʂ̍X�V���[�h	�ŏ����z�[��
	size_t checkUpdateMode = static_cast<size_t>(CheckUpdateMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* CheckUpdateMode[])();

	//�`�F�b�N��ʂ̕`�惂�[�h	�ŏ����z�[��
	size_t checkDrawMode = static_cast<size_t>(CheckDrawMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* CheckDrawMode[])();

	//�ҏW��ʂ̍X�V���[�h	�ŏ����z�[��
	size_t editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* EditUpdateMode[])();

	//�ҏW��ʂ̕`�惂�[�h	�ŏ����z�[��
	size_t editDrawMode = static_cast<size_t>(EditDrawMode::Home);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (TaskManager::* EditDrawMode[])();

private:
	//�����o�[
	std::list<Member>member;
	//�^�X�N
	std::list<Task>task;

private://�����o�ϐ�
	//�}�E�X�̍��W
	int mouseX, mouseY;
	int mouseClickTrigger, mouseClick, preMouseClick;

	float WindowWidth = 1024;
	float WindowHeight = 576;

	//�~�̍��W�A���a
	float circleRMax = 100;
	float circleRMin = 70;
	float circle1R;
	float circle2R;
	float circle3R;
	float circle4R;
	DirectX::XMFLOAT2 circle1Pos;
	DirectX::XMFLOAT2 circle2Pos;
	DirectX::XMFLOAT2 circle3Pos;
	DirectX::XMFLOAT2 circle4Pos;

	//�}�E�X���������Ă��邩�̔���
	bool circle1Flag = false;
	bool circle2Flag = false;
	bool circle3Flag = false;
	bool circle4Flag = false;

	//�����o�[�ǉ���ʂ̃t���O
	bool addIdFlag = false;
	bool addNameFlag = false;
	bool addClassNameFlag = false;
	//�����o�[�ǉ��p�̕�����
	std::string addId;
	std::string addName;
	std::string addClassName;

	//�����o�[�폜���̃����o�[�̃t���O
	std::vector<bool> deleteFlag;
	int memberNum = 0;
	
	//���͎��̏c���̓_�ŗp�^�C�}�[
	int timer = 0;

	int idInput;
	int nameInput;
	int classNameInput;

	//�^�X�N�p
	int taskNum = 0;
	std::vector<bool>taskFlag;

	int tInput0, tInput1, tInput2, tInput3, tInput4, tInput5;
	std::string add0, add1, add2, add3, add4, add5;
	bool addFlag0, addFlag1, addFlag2, addFlag3, addFlag4, addFlag5;

	bool editFlag = false;
};

