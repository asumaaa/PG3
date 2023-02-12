#define _CRT_SECURE_NO_WARNINGS
#include "TaskManager.h"
#include "DxLib.h"
#include "math.h"
#include "fstream"
#include "sstream"
#include <iostream>

TaskManager* TaskManager::GetInstance()
{
	static TaskManager instance;
	return &instance;
}

void TaskManager::Initialize()
{
	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);
	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);
	mouseClickTrigger = false;
	mouseClick = false;
	preMouseClick = false;

	member.clear();

	SetHome();
}

void TaskManager::Update()
{
	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);
	//�}�E�X�̃N���b�N���擾
	if (GetMouseInput() & MOUSE_INPUT_LEFT)mouseClick = 1;
	else { mouseClick = 0; }
	//�}�E�X�̃N���b�N�̃g���K�[�擾
	if (mouseClick == 1 && preMouseClick == 0)mouseClickTrigger = 1;
	else { mouseClickTrigger = 0; }

	//�^�C�}�[�X�V
	timer += 1;
	//60�t���[���Ń^�C�}�[��߂�
	if (timer >= 60)
	{
		timer = 0;
	}

	//�����蔻��擾
	float x1 = (float)mouseX - circle1Pos.x;
	float y1 = (float)mouseY - circle1Pos.y;
	float x2 = (float)mouseX - circle2Pos.x;
	float y2 = (float)mouseY - circle2Pos.y;
	float x3 = (float)mouseX - circle3Pos.x;
	float y3 = (float)mouseY - circle3Pos.y;
	float x4 = (float)mouseX - circle4Pos.x;
	float y4 = (float)mouseY - circle4Pos.y;
	float distance1 = sqrt((x1 * x1) + (y1 * y1));
	float distance2 = sqrt((x2 * x2) + (y2 * y2));
	float distance3 = sqrt((x3 * x3) + (y3 * y3));
	float distance4 = sqrt((x4 * x4) + (y4 * y4));
	if (distance1 <= circle1R) circle1Flag = true;
	else{ circle1Flag = false; }
	if (distance2 <= circle2R) circle2Flag = true;
	else { circle2Flag = false; }
	if (distance3 <= circle3R) circle3Flag = true;
	else { circle3Flag = false; }
	if (distance4 <= circle4R) circle4Flag = true;
	else { circle4Flag = false; }

	//���a�ύX
	if (circle1Flag)circle1R = circleRMax;
	else { circle1R = circleRMin; }
	if (circle2Flag)circle2R = circleRMax;
	else { circle2R = circleRMin; }
	if (circle3Flag)circle3R = circleRMax;
	else { circle3R = circleRMin; }
	if (circle4Flag)circle4R = circleRMax;
	else { circle4R = circleRMin; }

	//�V�[�����Ƃ̏���
	(this->*UpdateMode[updateMode])();

	//�O�̃t���[���̃}�E�X�N���b�N�ۑ�
	preMouseClick = mouseClick;
}

void TaskManager::Draw()
{
	//�V�[�����Ƃ̕`��
	(this->*DrawMode[drawMode])();
}

//�z�[����ʂ̍X�V
void TaskManager::HomeUpdate()
{
	//�V�[���ύX
	
	//�m�F��ʂ�
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Check);
		drawMode = static_cast<size_t>(DrawMode::Check);
		SetCheckHome();
	}

	//�ҏW��ʂ�
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Edit);
		drawMode = static_cast<size_t>(DrawMode::Edit);
		SetEditHome();
	}

	//�����o�[��ʂ�
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Member);
		drawMode = static_cast<size_t>(DrawMode::Member);
		SetMemberHome();
	}
}

//�`�F�b�N��ʂ̍X�V
void TaskManager::CheckUpdate()
{
	//�V�[�����Ƃ̍X�V
	(this->*CheckUpdateMode[checkUpdateMode])();
}

//�ҏW��ʂ̍X�V
void TaskManager::EditUpdate()
{
	//�V�[�����Ƃ̕`��
	(this->*EditUpdateMode[editUpdateMode])();
}

//�����o�[��ʂ̍X�V
void TaskManager::MenberUpdate()
{
	//�V�[�����Ƃ̍X�V
	(this->*MemberUpdateMode[memberUpdateMode])();
}

//�z�[����ʂ̕`��
void TaskManager::HomeDraw()
{
	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);

	//�����̕`��
	DrawFormatString(0, 0, 0x000000, "�^�X�N�Ǘ��c�[��");
	if (circle1Flag)DrawFormatString(100, 140, 0x000000, "���݂̃^�X�N�̊m�F���ł��܂�");
	if (circle2Flag)DrawFormatString(100, 140, 0x000000, "�^�X�N�̕ҏW���ł��܂�");
	if (circle3Flag)DrawFormatString(100, 140, 0x000000, "�����o�[�̕ҏW���ł��܂�");

	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�m�F");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�ҏW");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�����o�[");
}

//�`�F�b�N��ʂ̕`��
void TaskManager::CheckDraw()
{
	//�V�[�����Ƃ̍X�V
	(this->*CheckDrawMode[checkDrawMode])();
}

//�ҏW��ʂ̕`��
void TaskManager::EditDraw()
{
	//�V�[�����Ƃ̕`��
	(this->*EditDrawMode[editDrawMode])();
}

//�����o�[��ʂ̕`��
void TaskManager::MenberDraw()
{
	//�V�[�����Ƃ̕`��
	(this->*MemberDrawMode[memberDrawMode])();
}

//�����o�[��ʂ̃z�[�����
void TaskManager::MemberHomeUpdate()
{
	//�ǉ���ʂ�
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Add);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Add);
		SetMemberAdd();
	}

	//�폜��ʂ�
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Delete);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Delete);
		SetMemberDelete();
	}

	//�z�[����ʂ�
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Home);
		drawMode = static_cast<size_t>(DrawMode::Home);
		SetHome();
	}
}

//�����o�[��ʂ̒ǉ����
void TaskManager::MemberAddUpdate()
{
	//�}�E�X�N���b�N�Œǉ�����ꏊ��I��
	if (mouseX >= 100 && mouseX <= 800)
	{
		if (mouseY >= 150 && mouseY < 180 && mouseClickTrigger == true)
		{
			addIdFlag = true;
			addNameFlag = false;
			addClassNameFlag = false;
		}
		if (mouseY >= 180 && mouseY < 210 && mouseClickTrigger == true)
		{
			addIdFlag = false;
			addNameFlag = false;
			addClassNameFlag = true;
		}
		if (mouseY >= 210 && mouseY < 240 && mouseClickTrigger == true)
		{
			addIdFlag = false;
			addNameFlag = true;
			addClassNameFlag = false;
		}
	}

	//��������
	if (addIdFlag)
	{
		SetActiveKeyInput(idInput);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, idInput);
		addId = s0;
	}
	if (addNameFlag)
	{
		SetActiveKeyInput(nameInput);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, nameInput);
		addName = s0;
	}
	if (addClassNameFlag)
	{
		SetActiveKeyInput(classNameInput);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, classNameInput);
		addClassName = s0;
	}

	//�ۑ������Ƀz�[����
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();

		DeleteKeyInput(idInput);
		DeleteKeyInput(nameInput);
		DeleteKeyInput(classNameInput);
	}

	//�ۑ����ăz�[����
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//�ۑ�
		Member members(addId, addName, addClassName);
		member.emplace_back(members);

		//�t�@�C���ɏ�������
		std::ofstream ofs("member.csv");  // �t�@�C���p�X���w�肷��
		for (auto member : member)
		{
			ofs << "ID " << member.id << std::endl;
			ofs << "name " << member.name << std::endl;
			ofs << "class " << member.className << std::endl;
			ofs << " "<< std::endl;
		}

		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();

		DeleteKeyInput(idInput);
		DeleteKeyInput(nameInput);
		DeleteKeyInput(classNameInput);
	}
}

//�����o�[��ʂ̍폜���
void TaskManager::MemberDeleteUpdate()
{
	int distanceY = 20;
	//�}�E�X�N���b�N�ō폜����ꏊ��I��
	if (mouseX >= 30 && mouseX <= 800)
	{
		for (int i = 0; i < deleteFlag.size(); i++)
		{
			if (mouseY >= 90 + (distanceY * i) && mouseY < 90 + (distanceY * (i + 1)) 
				&& mouseClickTrigger == true)
			{
				deleteFlag[i] = true;
			}
			else if (mouseClickTrigger == true)
			{
				deleteFlag[i] = false;
			}
		}
	}

	//�폜�����Ƀz�[����
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();
	}

	//�폜���ăz�[����
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//�t�@�C���ɏ�������
		std::ofstream ofs("member.csv");  // �t�@�C���p�X���w�肷��
		int i = 0;
		for (auto member : member)
		{
			//�폜�t���O�������Ă��Ȃ������珑������
			if (deleteFlag[i] == false)
			{
				ofs << "ID " << member.id << std::endl;
				ofs << "name " << member.name << std::endl;
				ofs << "class " << member.className << std::endl;
				ofs << " " << std::endl;
			}
			i++;
		}

		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();
	}
}

//�����o�[��ʂ̃z�[�����
void TaskManager::MemberHomeDraw()
{
	// �����o�[���X�g�̕`��
		int i = 0;
	int distanceY = 20;
	for (auto member : member)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s �N���X:%s ���O:%s",
			member.id.c_str(), member.className.c_str(), member.name.c_str());
		i++;
	}

	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�ǉ�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�폜");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�߂�");
}

//�����o�[��ʂ̒ǉ����
void TaskManager::MemberAddDraw()
{
	DrawFormatString(100, 100, 0x000000, "�ǉ������������o�[�̏�����͂��Ă�������");

	//��
	DrawLine(100, 175,800,175, 0x000000);
	DrawLine(100, 205, 800, 205, 0x000000);
	DrawLine(100, 235, 800, 235, 0x000000);

	if (timer / 30 == 0)
	{
		DrawFormatString(100, 150, 0x000000, "ID:%s",addId.c_str());
		DrawFormatString(100, 180, 0x000000, "�N���X:%s", addClassName.c_str());
		DrawFormatString(100, 210, 0x000000, "���O:%s", addName.c_str());
	}
	if (timer / 30 == 1)
	{
		if (addIdFlag == true)DrawFormatString(100, 150, 0x000000, "ID:%s|",addId.c_str());
		else { DrawFormatString(100, 150, 0x000000, "ID:%s",addId.c_str()); }
		if (addClassNameFlag == true)DrawFormatString(100, 180, 0x000000, "�N���X:%s|", addClassName.c_str());
		else {DrawFormatString(100, 180, 0x000000, "�N���X:%s", addClassName.c_str());}
		if (addNameFlag == true)DrawFormatString(100, 210, 0x000000, "���O:%s|", addName.c_str());
		else { DrawFormatString(100, 210, 0x000000, "���O:%s", addName.c_str()); }
	}

	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�ۑ�");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�߂�");
}

//�����o�[��ʂ̍폜���
void TaskManager::MemberDeleteDraw()
{
	DrawFormatString(100, 50, 0x000000, "�폜�����������o�[��I��ł�������");

	// �����o�[���X�g�̕`��
	int i = 0;
	int distanceY = 20;
	for (auto member : member)
	{
		DrawFormatString(30, 90 + (distanceY * i), 0x000000,
			"ID:%s �N���X:%s ���O:%s",
			member.id.c_str(), member.className.c_str(), member.name.c_str());
		i++;
	}

	//�Z�̕`��
	for (int j = 0; j < deleteFlag.size(); j++)
	{
		if (deleteFlag[j] == true)
		{
			if (timer / 30 == 0)
			{
				DrawFormatString(10, 90 + (distanceY * j), 0x000000, "�~");
			}
		}
	}

	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�폜");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�߂�");
}

void TaskManager::CheckHomeUpdate()
{
	//�ǉ���ʂ�
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Home);
		drawMode = static_cast<size_t>(DrawMode::Home);
		SetHome();
	}
}

void TaskManager::CheckCheckUpdate()
{
}

void TaskManager::CheckHomeDraw()
{
	DrawFormatString(30, 20, 0x000000, "�^�X�N�ꗗ�ł�");

	int i = 0;
	int distanceY = 20;

	for (auto task : task)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s �S����:%s ���O:%s ���e:%s �D��x:%s ���:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}
	
	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
}

void TaskManager::CheckCheckDraw()
{
}

void TaskManager::EditHomeUpdate()
{
	//�z�[����ʂ�
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Home);
		drawMode = static_cast<size_t>(DrawMode::Home);
		SetHome();
	}

	//�폜��ʂ�
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Delete);
		editDrawMode = static_cast<size_t>(EditDrawMode::Delete);
		SetEditDelete();
	}

	//�ǉ���ʂ�
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Add);
		editDrawMode = static_cast<size_t>(EditDrawMode::Add);
		SetEditAdd();
	}

	//�ҏW��ʂ�
	if (circle4Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Edit);
		editDrawMode = static_cast<size_t>(EditDrawMode::Edit);
		SetEditEdit();
	}
}

void TaskManager::EditDeleteUpdate()
{
	int distanceY = 20;
	//�}�E�X�N���b�N�ō폜����ꏊ��I��
	if (mouseX >= 30 && mouseX <= 800)
	{
		for (int i = 0; i < taskFlag.size(); i++)
		{
			if (mouseY >= 90 + (distanceY * i) && mouseY < 90 + (distanceY * (i + 1))
				&& mouseClickTrigger == true)
			{
				taskFlag[i] = true;
			}
			else if (mouseClickTrigger == true)
			{
				taskFlag[i] = false;
			}
		}
	}

	//�폜�����Ƀz�[����
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
		editDrawMode = static_cast<size_t>(EditDrawMode::Home);
		SetEditHome();
	}

	//�폜���ăz�[����
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		int i = 0;
		
		//�t�@�C���ɏ�������
		std::ofstream ofs("task.csv");  // �t�@�C���p�X���w�肷��
		for (auto task : task)
		{
			//�폜�t���O�������Ă��Ȃ������珑������
			if (taskFlag[i] == false)
			{
				ofs << "ID " << task.id << std::endl;
				ofs << "manager " << task.manager << std::endl;
				ofs << "name " << task.name << std::endl;
				ofs << "content " << task.content << std::endl;
				ofs << "priority " << task.priority << std::endl;
				ofs << "state " << task.state << std::endl;
				ofs << " " << std::endl;
			}
			i++;
		}

		editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
		editDrawMode = static_cast<size_t>(EditDrawMode::Home);
		SetEditHome();
	}
}

void TaskManager::EditAddUpdate()
{
	//�}�E�X�N���b�N�Œǉ�����ꏊ��I��
	if (mouseX >= 100 && mouseX <= 800)
	{
		if (mouseY >= 150 && mouseY < 180 && mouseClickTrigger == true)
		{
			addFlag0 = true;
			addFlag1 = false;
			addFlag2 = false;
			addFlag3 = false;
			addFlag4 = false;
			addFlag5 = false;
		}
		if (mouseY >= 180 && mouseY < 210 && mouseClickTrigger == true)
		{
			addFlag0 = false;
			addFlag1 = true;
			addFlag2 = false;
			addFlag3 = false;
			addFlag4 = false;
			addFlag5 = false;
		}
		if (mouseY >= 210 && mouseY < 240 && mouseClickTrigger == true)
		{
			addFlag0 = false;
			addFlag1 = false;
			addFlag2 = true;
			addFlag3 = false;
			addFlag4 = false;
			addFlag5 = false;
		}
		if (mouseY >= 240 && mouseY < 270 && mouseClickTrigger == true)
		{
			addFlag0 = false;
			addFlag1 = false;
			addFlag2 = false;
			addFlag3 = true;
			addFlag4 = false;
			addFlag5 = false;
		}
		if (mouseY >= 270 && mouseY < 300 && mouseClickTrigger == true)
		{
			addFlag0 = false;
			addFlag1 = false;
			addFlag2 = false;
			addFlag3 = false;
			addFlag4 = true;
			addFlag5 = false;
		}
		if (mouseY >= 300 && mouseY < 330 && mouseClickTrigger == true)
		{
			addFlag0 = false;
			addFlag1 = false;
			addFlag2 = false;
			addFlag3 = false;
			addFlag4 = false;
			addFlag5 = true;
		}
	}

	//��������
	if (addFlag0)
	{
		SetActiveKeyInput(tInput0);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput0);
		add0 = s0;
	}
	if (addFlag1)
	{
		SetActiveKeyInput(tInput1);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput1);
		add1 = s0;
	}
	if (addFlag2)
	{
		SetActiveKeyInput(tInput2);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput2);
		add2 = s0;
	}
	if (addFlag3)
	{
		SetActiveKeyInput(tInput3);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput3);
		add3 = s0;
	}
	if (addFlag4)
	{
		SetActiveKeyInput(tInput4);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput4);
		add4 = s0;
	}
	if (addFlag5)
	{
		SetActiveKeyInput(tInput5);   // ���̓n���h�����A�N�e�B�u��

		char s0[256];

		// ���͂��ꂽ��������擾
		GetKeyInputString(s0, tInput5);
		add5 = s0;
	}

	//�ۑ������Ƀz�[����
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
		editDrawMode = static_cast<size_t>(EditDrawMode::Home);
		SetEditHome();

		DeleteKeyInput(tInput0);
		DeleteKeyInput(tInput1);
		DeleteKeyInput(tInput2);
		DeleteKeyInput(tInput3);
		DeleteKeyInput(tInput4);
		DeleteKeyInput(tInput5);
	}

	//�ۑ����ăz�[����
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//�ۑ�
		Task tasks(add0, add1, add2, add3, add4, add5);
		task.emplace_back(tasks);

		//�t�@�C���ɏ�������
		std::ofstream ofs("task.csv");  // �t�@�C���p�X���w�肷��
		for (auto task : task)
		{
			ofs << "ID " << task.id << std::endl;
			ofs << "manager " << task.manager << std::endl;
			ofs << "name " << task.name << std::endl;
			ofs << "content " << task.content << std::endl;
			ofs << "priority " << task.priority << std::endl;
			ofs << "state " << task.state << std::endl;
			ofs << " " << std::endl;
		}

		editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
		editDrawMode = static_cast<size_t>(EditDrawMode::Home);
		SetEditHome();

		DeleteKeyInput(tInput0);
		DeleteKeyInput(tInput1);
		DeleteKeyInput(tInput2);
		DeleteKeyInput(tInput3);
		DeleteKeyInput(tInput4);
		DeleteKeyInput(tInput5);
	}
}

void TaskManager::EditEditUpdate()
{
	
}

void TaskManager::EditHomeDraw()
{
	DrawFormatString(30, 20, 0x000000, "�^�X�N�ꗗ�ł�");

	int i = 0;
	int distanceY = 20;

	for (auto task : task)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s �S����:%s ���O:%s ���e:%s �D��x:%s ���:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}


	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawCircle(circle4Pos.x, circle4Pos.y, circle4R, 0x000000, true);
	DrawCircle(circle4Pos.x, circle4Pos.y, circle4R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�폜");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�ǉ�");
	DrawFormatString(circle4Pos.x, circle4Pos.y, 0x000000, "�ҏW");
}

void TaskManager::EditDeleteDraw()
{
	DrawFormatString(100, 50, 0x000000, "�폜�������^�X�N��I��ł�������");

	// �����o�[���X�g�̕`��
	int i = 0;
	int distanceY = 20;
	for (auto task : task)
	{
		DrawFormatString(30, 90 + (distanceY * i), 0x000000,
			"ID:%s �S����:%s ���O:%s ���e:%s �D��x:%s ���:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}

	//�Z�̕`��
	for (int j = 0; j < taskFlag.size(); j++)
	{
		if (taskFlag[j] == true)
		{
			if (timer / 30 == 0)
			{
				DrawFormatString(10, 90 + (distanceY * j), 0x000000, "�~");
			}
		}
	}

	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�폜");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�߂�");
}

void TaskManager::EditAddDraw()
{
	//�~�̕`��
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "�߂�");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "�ۑ�");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "�߂�");

	//��
	DrawLine(100, 175, 800, 175, 0x000000);
	DrawLine(100, 205, 800, 205, 0x000000);
	DrawLine(100, 235, 800, 235, 0x000000);
	DrawLine(100, 265, 800, 265, 0x000000);
	DrawLine(100, 295, 800, 295, 0x000000);
	DrawLine(100, 325, 800, 325, 0x000000);

	if (timer / 30 == 0)
	{
		DrawFormatString(100, 150, 0x000000, "ID:%s", add0.c_str());
		DrawFormatString(100, 180, 0x000000, "�S����:%s", add1.c_str());
		DrawFormatString(100, 210, 0x000000, "���O:%s", add2.c_str());
		DrawFormatString(100, 240, 0x000000, "���e:%s", add3.c_str());
		DrawFormatString(100, 270, 0x000000, "�D��x:%s", add4.c_str());
		DrawFormatString(100, 300, 0x000000, "�X�e�[�^�X:%s", add5.c_str());
	}
	if (timer / 30 == 1)
	{
		if (addFlag0 == true)DrawFormatString(100, 150, 0x000000, "ID:%s|", add0.c_str());
		else { DrawFormatString(100, 150, 0x000000, "ID:%s", add0.c_str()); }
		if (addFlag1 == true)DrawFormatString(100, 180, 0x000000, "�S����:%s|", add1.c_str());
		else { DrawFormatString(100, 180, 0x000000, "�S����:%s", add1.c_str()); }
		if (addFlag2 == true)DrawFormatString(100, 210, 0x000000, "���O:%s|", add2.c_str());
		else { DrawFormatString(100, 210, 0x000000, "���O:%s", add2.c_str()); }
		if (addFlag3 == true)DrawFormatString(100, 240, 0x000000, "���e:%s|", add3.c_str());
		else { DrawFormatString(100, 240, 0x000000, "���e:%s", add3.c_str()); }
		if (addFlag4 == true)DrawFormatString(100, 270, 0x000000, "�D��x:%s|", add4.c_str());
		else { DrawFormatString(100, 270, 0x000000, "�D��x:%s", add4.c_str()); }
		if (addFlag5 == true)DrawFormatString(100, 300, 0x000000, "�X�e�[�^�X:%s|", add5.c_str());
		else { DrawFormatString(100, 300, 0x000000, "�X�e�[�^�X:%s", add5.c_str()); }
	}
}

void TaskManager::EditEditDraw()
{
	
}

void TaskManager::SetHome()
{
	//�~1�̏����l
	circle1Pos = { WindowWidth * 0.25f,WindowHeight * 0.5f };
	//�~2�̏����l
	circle2Pos = { WindowWidth * 0.50f,WindowHeight * 0.5f };
	//�~3�̏����l
	circle3Pos = { WindowWidth * 0.75f,WindowHeight * 0.5f };
	//�~4�̏����l
	circle4Pos = { 10000,10000};

	circle1R = circleRMin;
	circle2R = circleRMin;
	circle3R = circleRMin;
	circle4R = circleRMin;
}

void TaskManager::SetMemberHome()
{
	//�~1�̏����l
	circle1Pos = { WindowWidth - 390,WindowHeight - 50};
	//�~2�̏����l
	circle2Pos = { WindowWidth - 220,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { WindowWidth - 50,WindowHeight - 50 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	memberNum = 0;

	//�����o�[�̃��X�g����U�N���A
	member.clear();

	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	file.open("member.csv");
	assert(!file.fail());

	std::string id;
	std::string name;
	std::string className;

	bool idFlag = false;
	bool nameFlag = false;
	bool classNameFlag = false;

	//1�s���ǂݍ���
	std::string  line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		getline(line_stream, key, ' ');

		if (key == "ID")
		{
			memberNum++;
			std::string ids;
			line_stream >> ids;
			id = ids;
			idFlag = true;
		}
		//�}�e���A��
		if (key == "name")
		{
			std::string names;
			line_stream >> names;
			name = names;
			nameFlag = true;
		}
		if (key == "class")
		{
			std::string classNames;
			line_stream >> classNames;
			className = classNames;
			classNameFlag = true;
		}
		//3���ׂĎ擾�ł�����
		if (idFlag && nameFlag && classNameFlag)
		{
			Member members(id, name, className);
			member.emplace_back(members);
			idFlag = false;
			classNameFlag = false;
			nameFlag = false;
		}
	}
	file.close();
}

void TaskManager::SetMemberAdd()
{
	//�~1�̏����l
	circle1Pos = { 50,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { 10000,10000 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	addId.clear();
	addName.clear();
	addClassName.clear();

	idInput = MakeKeyInput(80, FALSE, FALSE, FALSE);
	nameInput = MakeKeyInput(80, FALSE, FALSE, FALSE);
	classNameInput = MakeKeyInput(80, FALSE, FALSE, FALSE);
}

void TaskManager::SetMemberDelete()
{
	//�~1�̏����l
	circle1Pos = { 50,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { 10000,10000 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	//�폜�t���O�̃T�C�Y����
	deleteFlag.resize(memberNum);
	//�폜�t���O��������
	for (int i = 0; i < deleteFlag.size(); i++)
	{
		deleteFlag[i] = false;
	}
}

void TaskManager::SetCheckHome()
{
	//�~1�̏����l
	circle1Pos = { 70,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { 10000,10000 };
	//�~3�̏����l
	circle3Pos = { 10000,10000 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	taskNum = 0;

	//�����o�[�̃��X�g����U�N���A
	task.clear();

	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	file.open("task.csv");
	assert(!file.fail());

	std::string id;	//ID
	std::string manager;	//�S����
	std::string name;	//���O
	std::string content;	//���e�D��x
	std::string priority;	//�D��x
	std::string state;	//�X�e�[�^�X

	bool idFlag = false;
	bool managerFlag = false;
	bool nameFlag = false;
	bool contentFlag = false;
	bool priorityFlag = false;
	bool stateFlag = false;

	//1�s���ǂݍ���
	std::string  line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		getline(line_stream, key, ' ');

		if (key == "ID")
		{
			taskNum++;
			std::string ids;
			line_stream >> ids;
			id = ids;
			idFlag = true;
		}
		if (key == "manager")
		{
			std::string managers;
			line_stream >> managers;
			manager = managers;
			managerFlag = true;
		}
		if (key == "name")
		{
			std::string names;
			line_stream >> names;
			name = names;
			nameFlag = true;
		}
		if (key == "content")
		{
			std::string contents;
			line_stream >> contents;
			content = contents;
			contentFlag = true;
		}
		if (key == "priority")
		{
			std::string prioritys;
			line_stream >> prioritys;
			priority = prioritys;
			priorityFlag = true;
		}
		if (key == "state")
		{
			std::string states;
			line_stream >> states;
			state = states;
			stateFlag = true;
		}
		//6���ׂĎ擾�ł�����
		if (idFlag && managerFlag && nameFlag && contentFlag && priorityFlag && stateFlag)
		{
			Task tasks(id, manager, name,content,priority,state);
			task.emplace_back(tasks);
			idFlag = false;
			managerFlag = false;
			nameFlag = false;
			contentFlag = false;
			priorityFlag = false;
			stateFlag = false;
		}
	}
	file.close();

	taskFlag.resize(taskNum);
	for (int i = 0; i < taskFlag.size(); i++)
	{
		taskFlag[i] = false;
	}
}

void TaskManager::SetCheckCheck()
{
}

void TaskManager::SetEditHome()
{
	//�~1�̏����l
	circle1Pos = { WindowWidth * 1 / 4,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { WindowWidth * 2 / 4,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { WindowWidth * 3 / 4,WindowHeight - 50 };
	//�~4�̏����l
	circle4Pos = { 10000,WindowHeight - 50 };

	taskNum = 0;

	//�����o�[�̃��X�g����U�N���A
	task.clear();

	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	file.open("task.csv");
	assert(!file.fail());

	std::string id;	//ID
	std::string manager;	//�S����
	std::string name;	//���O
	std::string content;	//���e�D��x
	std::string priority;	//�D��x
	std::string state;	//�X�e�[�^�X

	bool idFlag = false;
	bool managerFlag = false;
	bool nameFlag = false;
	bool contentFlag = false;
	bool priorityFlag = false;
	bool stateFlag = false;

	//1�s���ǂݍ���
	std::string  line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		getline(line_stream, key, ' ');

		if (key == "ID")
		{
			taskNum++;
			std::string ids;
			line_stream >> ids;
			id = ids;
			idFlag = true;
		}
		if (key == "manager")
		{
			std::string managers;
			line_stream >> managers;
			manager = managers;
			managerFlag = true;
		}
		if (key == "name")
		{
			std::string names;
			line_stream >> names;
			name = names;
			nameFlag = true;
		}
		if (key == "content")
		{
			std::string contents;
			line_stream >> contents;
			content = contents;
			contentFlag = true;
		}
		if (key == "priority")
		{
			std::string prioritys;
			line_stream >> prioritys;
			priority = prioritys;
			priorityFlag = true;
		}
		if (key == "state")
		{
			std::string states;
			line_stream >> states;
			state = states;
			stateFlag = true;
		}
		//6���ׂĎ擾�ł�����
		if (idFlag && managerFlag && nameFlag && contentFlag && priorityFlag && stateFlag)
		{
			Task tasks(id, manager, name, content, priority, state);
			task.emplace_back(tasks);
			idFlag = false;
			managerFlag = false;
			nameFlag = false;
			contentFlag = false;
			priorityFlag = false;
			stateFlag = false;
		}
	}
	file.close();

	taskFlag.resize(taskNum);
	for (int i = 0; i < taskFlag.size(); i++)
	{
		taskFlag[i] = false;
	}
}

void TaskManager::SetEditDelete()
{
	//�~1�̏����l
	circle1Pos = { 50,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { 10000,10000 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	//�폜�t���O�̃T�C�Y����
	taskFlag.resize(taskNum);
	//�폜�t���O��������
	for (int i = 0; i < taskFlag.size(); i++)
	{
		taskFlag[i] = false;
	}
}

void TaskManager::SetEditAdd()
{
	//�~1�̏����l
	circle1Pos = { 50,WindowHeight - 50 };
	//�~2�̏����l
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//�~3�̏����l
	circle3Pos = { 10000,10000 };
	//�~4�̏����l
	circle4Pos = { 10000,10000 };

	add0.clear();
	add1.clear();
	add2.clear();
	add3.clear();
	add4.clear();
	add5.clear();

	tInput0 = MakeKeyInput(80, FALSE, FALSE, FALSE);
	tInput1 = MakeKeyInput(80, FALSE, FALSE, FALSE);
	tInput2 = MakeKeyInput(80, FALSE, FALSE, FALSE);
	tInput3 = MakeKeyInput(80, FALSE, FALSE, FALSE);
	tInput4 = MakeKeyInput(80, FALSE, FALSE, FALSE);
	tInput5 = MakeKeyInput(80, FALSE, FALSE, FALSE);
}

void TaskManager::SetEditEdit()
{
}

void (TaskManager::* TaskManager::UpdateMode[])() =
{
	&TaskManager::HomeUpdate,
	&TaskManager::CheckUpdate,
	&TaskManager::EditUpdate,
	&TaskManager::MenberUpdate,
};

void (TaskManager::* TaskManager::DrawMode[])() =
{
	&TaskManager::HomeDraw,
	&TaskManager::CheckDraw,
	&TaskManager::EditDraw,
	&TaskManager::MenberDraw,
};

void (TaskManager::* TaskManager::MemberUpdateMode[])() =
{
	&TaskManager::MemberHomeUpdate,
	&TaskManager::MemberAddUpdate,
	&TaskManager::MemberDeleteUpdate,
};

void (TaskManager::* TaskManager::MemberDrawMode[])() =
{
	&TaskManager::MemberHomeDraw,
	&TaskManager::MemberAddDraw,
	&TaskManager::MemberDeleteDraw,
};

void (TaskManager::* TaskManager::CheckUpdateMode[])() =
{
	&TaskManager::CheckHomeUpdate,
	&TaskManager::CheckCheckUpdate,
};

void (TaskManager::* TaskManager::CheckDrawMode[])() =
{
	&TaskManager::CheckHomeDraw,
	&TaskManager::CheckCheckDraw,
};

void (TaskManager::* TaskManager::EditUpdateMode[])() =
{
	&TaskManager::EditHomeUpdate,
	&TaskManager::EditDeleteUpdate,
	&TaskManager::EditAddUpdate,
	&TaskManager::EditEditUpdate,
};

void (TaskManager::* TaskManager::EditDrawMode[])() =
{
	&TaskManager::EditHomeDraw,
	&TaskManager::EditDeleteDraw,
	&TaskManager::EditAddDraw,
	&TaskManager::EditEditDraw,
};