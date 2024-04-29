#include "SceneResult.h"

//初期化
void RESULT::Init()
{
	BackHandle = 0;	//背景画像初期化

	//ループリザルトへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
//ロード
void RESULT::Load()
{
	//背景画像読み込み
	BackHandle = LoadGraph("Data/Image/Result/BackResult.png");
}
void RESULT::Sound()
{
}

//通常処理
void RESULT::Step()
{
	//タイトルシーンへの遷移
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//シーンフラグをタイトルシーンに変更
		m_SceneFlag = 0;
		//リザルト後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
}

//描画処理
void RESULT::Draw()
{
	DrawGraph(0, 0, BackHandle, true);	//背景
}

//後処理
void RESULT::Fin()
{
	DeleteGraph(BackHandle);	//背景画像破棄
	//タイトル初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}