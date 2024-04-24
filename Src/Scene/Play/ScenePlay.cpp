#pragma once

#include "ScenePlay.h"
#include "../../Common.h"

#define NUM_DANGO_PATH "Data/Dango/dango1"

//=============================
// プレイシーン
//=============================

//初期化
void PLAY::Init()
{
	m_numhndl = 0;

	//プレイループへ
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//ロード
void PLAY::Load()
{
	m_numhndl = LoadGraph(NUM_DANGO_PATH);
}

void PLAY::Sound()
{

}

//通常処理
void PLAY::Step()
{

	//if (flamecount > 60)
	//{
	//	//シーンフラグをリザルトシーンに変更
	//	m_SceneFlag = 0;
	//	//プレイ後処理へ移動
	//	g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	//}
}

//描画処理
void PLAY::Draw()
{
	DrawGraph(600, 600, m_numhndl, true);
}

//後処理
void PLAY::Fin()
{

}

