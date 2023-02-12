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
	// マウスを表示状態にする
	SetMouseDispFlag(TRUE);
	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);
	mouseClickTrigger = false;
	mouseClick = false;
	preMouseClick = false;

	member.clear();

	SetHome();
}

void TaskManager::Update()
{
	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);
	//マウスのクリックを取得
	if (GetMouseInput() & MOUSE_INPUT_LEFT)mouseClick = 1;
	else { mouseClick = 0; }
	//マウスのクリックのトリガー取得
	if (mouseClick == 1 && preMouseClick == 0)mouseClickTrigger = 1;
	else { mouseClickTrigger = 0; }

	//タイマー更新
	timer += 1;
	//60フレームでタイマーを戻す
	if (timer >= 60)
	{
		timer = 0;
	}

	//当たり判定取得
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

	//半径変更
	if (circle1Flag)circle1R = circleRMax;
	else { circle1R = circleRMin; }
	if (circle2Flag)circle2R = circleRMax;
	else { circle2R = circleRMin; }
	if (circle3Flag)circle3R = circleRMax;
	else { circle3R = circleRMin; }
	if (circle4Flag)circle4R = circleRMax;
	else { circle4R = circleRMin; }

	//シーンごとの処理
	(this->*UpdateMode[updateMode])();

	//前のフレームのマウスクリック保存
	preMouseClick = mouseClick;
}

void TaskManager::Draw()
{
	//シーンごとの描画
	(this->*DrawMode[drawMode])();
}

//ホーム画面の更新
void TaskManager::HomeUpdate()
{
	//シーン変更
	
	//確認画面へ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Check);
		drawMode = static_cast<size_t>(DrawMode::Check);
		SetCheckHome();
	}

	//編集画面へ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Edit);
		drawMode = static_cast<size_t>(DrawMode::Edit);
		SetEditHome();
	}

	//メンバー画面へ
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Member);
		drawMode = static_cast<size_t>(DrawMode::Member);
		SetMemberHome();
	}
}

//チェック画面の更新
void TaskManager::CheckUpdate()
{
	//シーンごとの更新
	(this->*CheckUpdateMode[checkUpdateMode])();
}

//編集画面の更新
void TaskManager::EditUpdate()
{
	//シーンごとの描画
	(this->*EditUpdateMode[editUpdateMode])();
}

//メンバー画面の更新
void TaskManager::MenberUpdate()
{
	//シーンごとの更新
	(this->*MemberUpdateMode[memberUpdateMode])();
}

//ホーム画面の描画
void TaskManager::HomeDraw()
{
	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);

	//文字の描画
	DrawFormatString(0, 0, 0x000000, "タスク管理ツール");
	if (circle1Flag)DrawFormatString(100, 140, 0x000000, "現在のタスクの確認ができます");
	if (circle2Flag)DrawFormatString(100, 140, 0x000000, "タスクの編集ができます");
	if (circle3Flag)DrawFormatString(100, 140, 0x000000, "メンバーの編集ができます");

	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "確認");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "編集");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "メンバー");
}

//チェック画面の描画
void TaskManager::CheckDraw()
{
	//シーンごとの更新
	(this->*CheckDrawMode[checkDrawMode])();
}

//編集画面の描画
void TaskManager::EditDraw()
{
	//シーンごとの描画
	(this->*EditDrawMode[editDrawMode])();
}

//メンバー画面の描画
void TaskManager::MenberDraw()
{
	//シーンごとの描画
	(this->*MemberDrawMode[memberDrawMode])();
}

//メンバー画面のホーム画面
void TaskManager::MemberHomeUpdate()
{
	//追加画面へ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Add);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Add);
		SetMemberAdd();
	}

	//削除画面へ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Delete);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Delete);
		SetMemberDelete();
	}

	//ホーム画面へ
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Home);
		drawMode = static_cast<size_t>(DrawMode::Home);
		SetHome();
	}
}

//メンバー画面の追加画面
void TaskManager::MemberAddUpdate()
{
	//マウスクリックで追加する場所を選択
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

	//文字入力
	if (addIdFlag)
	{
		SetActiveKeyInput(idInput);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, idInput);
		addId = s0;
	}
	if (addNameFlag)
	{
		SetActiveKeyInput(nameInput);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, nameInput);
		addName = s0;
	}
	if (addClassNameFlag)
	{
		SetActiveKeyInput(classNameInput);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, classNameInput);
		addClassName = s0;
	}

	//保存せずにホームへ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();

		DeleteKeyInput(idInput);
		DeleteKeyInput(nameInput);
		DeleteKeyInput(classNameInput);
	}

	//保存してホームへ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//保存
		Member members(addId, addName, addClassName);
		member.emplace_back(members);

		//ファイルに書き込み
		std::ofstream ofs("member.csv");  // ファイルパスを指定する
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

//メンバー画面の削除画面
void TaskManager::MemberDeleteUpdate()
{
	int distanceY = 20;
	//マウスクリックで削除する場所を選択
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

	//削除せずにホームへ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
		memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
		SetMemberHome();
	}

	//削除してホームへ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//ファイルに書き込み
		std::ofstream ofs("member.csv");  // ファイルパスを指定する
		int i = 0;
		for (auto member : member)
		{
			//削除フラグが立っていなかったら書き込み
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

//メンバー画面のホーム画面
void TaskManager::MemberHomeDraw()
{
	// メンバーリストの描画
		int i = 0;
	int distanceY = 20;
	for (auto member : member)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s クラス:%s 名前:%s",
			member.id.c_str(), member.className.c_str(), member.name.c_str());
		i++;
	}

	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "追加");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "削除");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "戻る");
}

//メンバー画面の追加画面
void TaskManager::MemberAddDraw()
{
	DrawFormatString(100, 100, 0x000000, "追加したいメンバーの情報を入力してください");

	//線
	DrawLine(100, 175,800,175, 0x000000);
	DrawLine(100, 205, 800, 205, 0x000000);
	DrawLine(100, 235, 800, 235, 0x000000);

	if (timer / 30 == 0)
	{
		DrawFormatString(100, 150, 0x000000, "ID:%s",addId.c_str());
		DrawFormatString(100, 180, 0x000000, "クラス:%s", addClassName.c_str());
		DrawFormatString(100, 210, 0x000000, "名前:%s", addName.c_str());
	}
	if (timer / 30 == 1)
	{
		if (addIdFlag == true)DrawFormatString(100, 150, 0x000000, "ID:%s|",addId.c_str());
		else { DrawFormatString(100, 150, 0x000000, "ID:%s",addId.c_str()); }
		if (addClassNameFlag == true)DrawFormatString(100, 180, 0x000000, "クラス:%s|", addClassName.c_str());
		else {DrawFormatString(100, 180, 0x000000, "クラス:%s", addClassName.c_str());}
		if (addNameFlag == true)DrawFormatString(100, 210, 0x000000, "名前:%s|", addName.c_str());
		else { DrawFormatString(100, 210, 0x000000, "名前:%s", addName.c_str()); }
	}

	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "保存");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "戻る");
}

//メンバー画面の削除画面
void TaskManager::MemberDeleteDraw()
{
	DrawFormatString(100, 50, 0x000000, "削除したいメンバーを選んでください");

	// メンバーリストの描画
	int i = 0;
	int distanceY = 20;
	for (auto member : member)
	{
		DrawFormatString(30, 90 + (distanceY * i), 0x000000,
			"ID:%s クラス:%s 名前:%s",
			member.id.c_str(), member.className.c_str(), member.name.c_str());
		i++;
	}

	//〇の描画
	for (int j = 0; j < deleteFlag.size(); j++)
	{
		if (deleteFlag[j] == true)
		{
			if (timer / 30 == 0)
			{
				DrawFormatString(10, 90 + (distanceY * j), 0x000000, "×");
			}
		}
	}

	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "削除");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "戻る");
}

void TaskManager::CheckHomeUpdate()
{
	//追加画面へ
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
	DrawFormatString(30, 20, 0x000000, "タスク一覧です");

	int i = 0;
	int distanceY = 20;

	for (auto task : task)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s 担当者:%s 名前:%s 内容:%s 優先度:%s 状態:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}
	
	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
}

void TaskManager::CheckCheckDraw()
{
}

void TaskManager::EditHomeUpdate()
{
	//ホーム画面へ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		updateMode = static_cast<size_t>(UpdateMode::Home);
		drawMode = static_cast<size_t>(DrawMode::Home);
		SetHome();
	}

	//削除画面へ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Delete);
		editDrawMode = static_cast<size_t>(EditDrawMode::Delete);
		SetEditDelete();
	}

	//追加画面へ
	if (circle3Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Add);
		editDrawMode = static_cast<size_t>(EditDrawMode::Add);
		SetEditAdd();
	}

	//編集画面へ
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
	//マウスクリックで削除する場所を選択
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

	//削除せずにホームへ
	if (circle1Flag == true && mouseClickTrigger == 1)
	{
		editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
		editDrawMode = static_cast<size_t>(EditDrawMode::Home);
		SetEditHome();
	}

	//削除してホームへ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		int i = 0;
		
		//ファイルに書き込み
		std::ofstream ofs("task.csv");  // ファイルパスを指定する
		for (auto task : task)
		{
			//削除フラグが立っていなかったら書き込み
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
	//マウスクリックで追加する場所を選択
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

	//文字入力
	if (addFlag0)
	{
		SetActiveKeyInput(tInput0);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput0);
		add0 = s0;
	}
	if (addFlag1)
	{
		SetActiveKeyInput(tInput1);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput1);
		add1 = s0;
	}
	if (addFlag2)
	{
		SetActiveKeyInput(tInput2);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput2);
		add2 = s0;
	}
	if (addFlag3)
	{
		SetActiveKeyInput(tInput3);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput3);
		add3 = s0;
	}
	if (addFlag4)
	{
		SetActiveKeyInput(tInput4);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput4);
		add4 = s0;
	}
	if (addFlag5)
	{
		SetActiveKeyInput(tInput5);   // 入力ハンドルをアクティブに

		char s0[256];

		// 入力された文字列を取得
		GetKeyInputString(s0, tInput5);
		add5 = s0;
	}

	//保存せずにホームへ
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

	//保存してホームへ
	if (circle2Flag == true && mouseClickTrigger == 1)
	{
		//保存
		Task tasks(add0, add1, add2, add3, add4, add5);
		task.emplace_back(tasks);

		//ファイルに書き込み
		std::ofstream ofs("task.csv");  // ファイルパスを指定する
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
	DrawFormatString(30, 20, 0x000000, "タスク一覧です");

	int i = 0;
	int distanceY = 20;

	for (auto task : task)
	{
		DrawFormatString(30, 50 + (distanceY * i), 0x000000,
			"ID:%s 担当者:%s 名前:%s 内容:%s 優先度:%s 状態:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}


	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawCircle(circle4Pos.x, circle4Pos.y, circle4R, 0x000000, true);
	DrawCircle(circle4Pos.x, circle4Pos.y, circle4R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "削除");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "追加");
	DrawFormatString(circle4Pos.x, circle4Pos.y, 0x000000, "編集");
}

void TaskManager::EditDeleteDraw()
{
	DrawFormatString(100, 50, 0x000000, "削除したいタスクを選んでください");

	// メンバーリストの描画
	int i = 0;
	int distanceY = 20;
	for (auto task : task)
	{
		DrawFormatString(30, 90 + (distanceY * i), 0x000000,
			"ID:%s 担当者:%s 名前:%s 内容:%s 優先度:%s 状態:%s",
			task.id.c_str(), task.manager.c_str(), task.name.c_str(), task.content.c_str()
			, task.priority.c_str(), task.state.c_str());
		i++;
	}

	//〇の描画
	for (int j = 0; j < taskFlag.size(); j++)
	{
		if (taskFlag[j] == true)
		{
			if (timer / 30 == 0)
			{
				DrawFormatString(10, 90 + (distanceY * j), 0x000000, "×");
			}
		}
	}

	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "削除");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "戻る");
}

void TaskManager::EditAddDraw()
{
	//円の描画
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R, 0x000000, true);
	DrawCircle(circle1Pos.x, circle1Pos.y, circle1R - 5.0f, 0xdddddd, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R, 0x000000, true);
	DrawCircle(circle2Pos.x, circle2Pos.y, circle2R - 5.0f, 0xdddddd, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R, 0x000000, true);
	DrawCircle(circle3Pos.x, circle3Pos.y, circle3R - 5.0f, 0xdddddd, true);
	DrawFormatString(circle1Pos.x, circle1Pos.y, 0x000000, "戻る");
	DrawFormatString(circle2Pos.x, circle2Pos.y, 0x000000, "保存");
	DrawFormatString(circle3Pos.x, circle3Pos.y, 0x000000, "戻る");

	//線
	DrawLine(100, 175, 800, 175, 0x000000);
	DrawLine(100, 205, 800, 205, 0x000000);
	DrawLine(100, 235, 800, 235, 0x000000);
	DrawLine(100, 265, 800, 265, 0x000000);
	DrawLine(100, 295, 800, 295, 0x000000);
	DrawLine(100, 325, 800, 325, 0x000000);

	if (timer / 30 == 0)
	{
		DrawFormatString(100, 150, 0x000000, "ID:%s", add0.c_str());
		DrawFormatString(100, 180, 0x000000, "担当者:%s", add1.c_str());
		DrawFormatString(100, 210, 0x000000, "名前:%s", add2.c_str());
		DrawFormatString(100, 240, 0x000000, "内容:%s", add3.c_str());
		DrawFormatString(100, 270, 0x000000, "優先度:%s", add4.c_str());
		DrawFormatString(100, 300, 0x000000, "ステータス:%s", add5.c_str());
	}
	if (timer / 30 == 1)
	{
		if (addFlag0 == true)DrawFormatString(100, 150, 0x000000, "ID:%s|", add0.c_str());
		else { DrawFormatString(100, 150, 0x000000, "ID:%s", add0.c_str()); }
		if (addFlag1 == true)DrawFormatString(100, 180, 0x000000, "担当者:%s|", add1.c_str());
		else { DrawFormatString(100, 180, 0x000000, "担当者:%s", add1.c_str()); }
		if (addFlag2 == true)DrawFormatString(100, 210, 0x000000, "名前:%s|", add2.c_str());
		else { DrawFormatString(100, 210, 0x000000, "名前:%s", add2.c_str()); }
		if (addFlag3 == true)DrawFormatString(100, 240, 0x000000, "内容:%s|", add3.c_str());
		else { DrawFormatString(100, 240, 0x000000, "内容:%s", add3.c_str()); }
		if (addFlag4 == true)DrawFormatString(100, 270, 0x000000, "優先度:%s|", add4.c_str());
		else { DrawFormatString(100, 270, 0x000000, "優先度:%s", add4.c_str()); }
		if (addFlag5 == true)DrawFormatString(100, 300, 0x000000, "ステータス:%s|", add5.c_str());
		else { DrawFormatString(100, 300, 0x000000, "ステータス:%s", add5.c_str()); }
	}
}

void TaskManager::EditEditDraw()
{
	
}

void TaskManager::SetHome()
{
	//円1の初期値
	circle1Pos = { WindowWidth * 0.25f,WindowHeight * 0.5f };
	//円2の初期値
	circle2Pos = { WindowWidth * 0.50f,WindowHeight * 0.5f };
	//円3の初期値
	circle3Pos = { WindowWidth * 0.75f,WindowHeight * 0.5f };
	//円4の初期値
	circle4Pos = { 10000,10000};

	circle1R = circleRMin;
	circle2R = circleRMin;
	circle3R = circleRMin;
	circle4R = circleRMin;
}

void TaskManager::SetMemberHome()
{
	//円1の初期値
	circle1Pos = { WindowWidth - 390,WindowHeight - 50};
	//円2の初期値
	circle2Pos = { WindowWidth - 220,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { WindowWidth - 50,WindowHeight - 50 };
	//円4の初期値
	circle4Pos = { 10000,10000 };

	memberNum = 0;

	//メンバーのリストを一旦クリア
	member.clear();

	//ファイルストリーム
	std::ifstream file;
	//objファイルを開く
	file.open("member.csv");
	assert(!file.fail());

	std::string id;
	std::string name;
	std::string className;

	bool idFlag = false;
	bool nameFlag = false;
	bool classNameFlag = false;

	//1行ずつ読み込む
	std::string  line;
	while (getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		//半角スペース区切りで行の先頭文字列を取得
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
		//マテリアル
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
		//3つすべて取得できたら
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
	//円1の初期値
	circle1Pos = { 50,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { 10000,10000 };
	//円4の初期値
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
	//円1の初期値
	circle1Pos = { 50,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { 10000,10000 };
	//円4の初期値
	circle4Pos = { 10000,10000 };

	//削除フラグのサイズ決定
	deleteFlag.resize(memberNum);
	//削除フラグを初期化
	for (int i = 0; i < deleteFlag.size(); i++)
	{
		deleteFlag[i] = false;
	}
}

void TaskManager::SetCheckHome()
{
	//円1の初期値
	circle1Pos = { 70,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { 10000,10000 };
	//円3の初期値
	circle3Pos = { 10000,10000 };
	//円4の初期値
	circle4Pos = { 10000,10000 };

	taskNum = 0;

	//メンバーのリストを一旦クリア
	task.clear();

	//ファイルストリーム
	std::ifstream file;
	//objファイルを開く
	file.open("task.csv");
	assert(!file.fail());

	std::string id;	//ID
	std::string manager;	//担当者
	std::string name;	//名前
	std::string content;	//内容優先度
	std::string priority;	//優先度
	std::string state;	//ステータス

	bool idFlag = false;
	bool managerFlag = false;
	bool nameFlag = false;
	bool contentFlag = false;
	bool priorityFlag = false;
	bool stateFlag = false;

	//1行ずつ読み込む
	std::string  line;
	while (getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		//半角スペース区切りで行の先頭文字列を取得
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
		//6つすべて取得できたら
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
	//円1の初期値
	circle1Pos = { WindowWidth * 1 / 4,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { WindowWidth * 2 / 4,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { WindowWidth * 3 / 4,WindowHeight - 50 };
	//円4の初期値
	circle4Pos = { 10000,WindowHeight - 50 };

	taskNum = 0;

	//メンバーのリストを一旦クリア
	task.clear();

	//ファイルストリーム
	std::ifstream file;
	//objファイルを開く
	file.open("task.csv");
	assert(!file.fail());

	std::string id;	//ID
	std::string manager;	//担当者
	std::string name;	//名前
	std::string content;	//内容優先度
	std::string priority;	//優先度
	std::string state;	//ステータス

	bool idFlag = false;
	bool managerFlag = false;
	bool nameFlag = false;
	bool contentFlag = false;
	bool priorityFlag = false;
	bool stateFlag = false;

	//1行ずつ読み込む
	std::string  line;
	while (getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		//半角スペース区切りで行の先頭文字列を取得
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
		//6つすべて取得できたら
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
	//円1の初期値
	circle1Pos = { 50,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { 10000,10000 };
	//円4の初期値
	circle4Pos = { 10000,10000 };

	//削除フラグのサイズ決定
	taskFlag.resize(taskNum);
	//削除フラグを初期化
	for (int i = 0; i < taskFlag.size(); i++)
	{
		taskFlag[i] = false;
	}
}

void TaskManager::SetEditAdd()
{
	//円1の初期値
	circle1Pos = { 50,WindowHeight - 50 };
	//円2の初期値
	circle2Pos = { WindowWidth - 100,WindowHeight - 50 };
	//円3の初期値
	circle3Pos = { 10000,10000 };
	//円4の初期値
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