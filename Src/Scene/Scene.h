#pragma once

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

enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//メインメニュー関連
	SCENE_ID_INIT_MEIN_MENU = 200,
	SCENE_ID_LOOP_MEIN_MENU,
	SCENE_ID_FIN_MEIN_MENU,

	//プレイ関連
	SCENE_ID_INIT_PLAY = 300,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//リザルト関連
	SCENE_ID_INIT_RESULT = 400,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};
//現在のシーンID
extern int g_CurrentSceneID;

