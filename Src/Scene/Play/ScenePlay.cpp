#pragma once
#include "ScenePlay.h"

//=============================
// プレイシーン
//=============================

//初期化
void PLAY::Init()
{
	BackHandle = 0;		//背景画像初期化

	m_cDango.Init();	//団子初期化

	//プレイループへ
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//ロード
void PLAY::Load()
{
	BackHandle = LoadGraph("Data/Image/Play/BackPlay.png");
	m_cDango.Load();	//団子ロード
}

void PLAY::Sound()
{

}

//通常処理
void PLAY::Step()
{
	m_cDango.Step();	//団子ステップ

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//シーンフラグをリザルトシーンに変更
		m_SceneFlag = 0;

		//プレイ後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
}

//描画処理
void PLAY::Draw()
{
	DrawGraph(0, 0, BackHandle, true);	//背景
	m_cDango.Draw();	//団子・串
}

//後処理
void PLAY::Fin()
{
	DeleteGraph(BackHandle);	//背景画像破棄
	m_cDango.Fin();		//団子後処理

	//リザルト初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
