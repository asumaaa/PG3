#pragma once
#include "DirectXMath.h"
#include "memory"
#include "list"
#include "string"
#include "vector"

class TaskManager
{
private:
	//更新モード
	enum class UpdateMode {
		Home,
		Check,
		Edit,
		Member,
	};
	//描画モード
	enum class DrawMode {
		Home,
		Check,
		Edit,
		Member,
	};

	//メンバー画面の更新モード
	enum class MemberUpdateMode {
		Home,
		Add,
		Delete,
	};
	//メンバー画面の描画モード
	enum class MemberDrawMode {
		Home,
		Add,
		Delete,
	};

	//チェック画面の更新モード
	enum class CheckUpdateMode {
		Home,
		Chack,
	};
	//チェック画面の描画モード
	enum class CheckDrawMode {
		Home,
		Chack,
	};

	//編集画面の更新モード
	enum class EditUpdateMode {
		Home,
		Delete,
		Add,
		Edit,
	};
	//編集画面の描画モード
	enum class EditDrawMode {
		Home,
		Delete,
		Add,
		Edit,
	};

	//メンバー
	struct Member
	{
		std::string id;	//ID
		std::string name;	//名前
		std::string className;	//所属しているクラス
		//コンストラクタ
		Member(std::string id, std::string name, std::string className)
		{
			this->id = id;
			this->name = name;
			this->className = className;
		};
	};

	//タスク
	struct Task
	{
		std::string id;	//ID
		std::string manager;	//担当者
		std::string name;	//名前
		std::string content;	//内容
		std::string priority;	//優先度
		std::string state;	//ステータス

		//コンストラクタ
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
public:	//メンバ関数
	//シングルトンインスタンスを取得
	static TaskManager*GetInstance();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

private://メンバ関数
	//各モードごとの更新
	void HomeUpdate();
	void CheckUpdate();
	void EditUpdate();
	void MenberUpdate();

	//各モードごとの描画
	void HomeDraw();
	void CheckDraw();
	void EditDraw();
	void MenberDraw();

	//メンバー画面の更新
	void MemberHomeUpdate();
	void MemberAddUpdate();
	void MemberDeleteUpdate();

	//メンバー画面の描画
	void MemberHomeDraw();
	void MemberAddDraw();
	void MemberDeleteDraw();

	//チェック画面の更新
	void CheckHomeUpdate();
	void CheckCheckUpdate();

	//チェック画面の更新
	void CheckHomeDraw();
	void CheckCheckDraw();

	//編集画面の更新
	void EditHomeUpdate();
	void EditDeleteUpdate();
	void EditAddUpdate();
	void EditEditUpdate();

	//編集画面の描画
	void EditHomeDraw();
	void EditDeleteDraw();
	void EditAddDraw();
	void EditEditDraw();

	//各モードに移動する際に呼ぶ関数
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
	//更新モード	最初がホーム
	size_t updateMode = static_cast<size_t>(UpdateMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* UpdateMode[])();

	//描画モード	最初がホーム
	size_t drawMode = static_cast<size_t>(DrawMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* DrawMode[])();

	//メンバー画面の更新モード	最初がホーム
	size_t memberUpdateMode = static_cast<size_t>(MemberUpdateMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* MemberUpdateMode[])();

	//メンバー画面の描画モード	最初がホーム
	size_t memberDrawMode = static_cast<size_t>(MemberDrawMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* MemberDrawMode[])();

	//チェック画面の更新モード	最初がホーム
	size_t checkUpdateMode = static_cast<size_t>(CheckUpdateMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* CheckUpdateMode[])();

	//チェック画面の描画モード	最初がホーム
	size_t checkDrawMode = static_cast<size_t>(CheckDrawMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* CheckDrawMode[])();

	//編集画面の更新モード	最初がホーム
	size_t editUpdateMode = static_cast<size_t>(EditUpdateMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* EditUpdateMode[])();

	//編集画面の描画モード	最初がホーム
	size_t editDrawMode = static_cast<size_t>(EditDrawMode::Home);
	//メンバ関数のポインタテーブル
	static void (TaskManager::* EditDrawMode[])();

private:
	//メンバー
	std::list<Member>member;
	//タスク
	std::list<Task>task;

private://メンバ変数
	//マウスの座標
	int mouseX, mouseY;
	int mouseClickTrigger, mouseClick, preMouseClick;

	float WindowWidth = 1024;
	float WindowHeight = 576;

	//円の座標、半径
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

	//マウスが当たっているかの判定
	bool circle1Flag = false;
	bool circle2Flag = false;
	bool circle3Flag = false;
	bool circle4Flag = false;

	//メンバー追加画面のフラグ
	bool addIdFlag = false;
	bool addNameFlag = false;
	bool addClassNameFlag = false;
	//メンバー追加用の文字列
	std::string addId;
	std::string addName;
	std::string addClassName;

	//メンバー削除時のメンバーのフラグ
	std::vector<bool> deleteFlag;
	int memberNum = 0;
	
	//入力時の縦線の点滅用タイマー
	int timer = 0;

	int idInput;
	int nameInput;
	int classNameInput;

	//タスク用
	int taskNum = 0;
	std::vector<bool>taskFlag;

	int tInput0, tInput1, tInput2, tInput3, tInput4, tInput5;
	std::string add0, add1, add2, add3, add4, add5;
	bool addFlag0, addFlag1, addFlag2, addFlag3, addFlag4, addFlag5;

	bool editFlag = false;
};

