#pragma once
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Common.h"
#include "../Input/Input.h"

//シーンIDの種類
enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//プレイ関連
	SCENE_ID_INIT_PLAY = 200,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//ゲームクリア関連
	SCENE_ID_INIT_RESULT = 300,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,
};

//シーンベースクラス
class SCENE_BASE
{
	protected:

		//シーンフラグ
		int m_SceneFlag;
		//シーンフレーム
		int m_SceneFlame;
	
	public:

		//初期化
		void virtual Init();
		//データロード
		void virtual Load();
		//通常処理
		void virtual Step();
		//描画処理
		void virtual Draw();
		//後処理
		void virtual Fin();
};

//現在のシーンID
extern int g_CurrentSceneID;
