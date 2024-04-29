#pragma once
#include "ScenePlay.h"

//=============================
// プレイシーン
//=============================

//初期化
void PLAY::Init()
{
	for (int i = 0; i < 2; i++)
	{
		BackHandle[i] = 0;		//背景画像初期化
	}

	for (int i = 0; i < 2; i++)
	{
		TextHandle[i] = 0;	//文字画像ハンドル
	}

	PosY[0] = 0;
	PosY[1] = -720;

	isDraw = false;

	Fade = 0;

	BGM = 0;			//BGM初期化
	SE = 0;				//効果音初期化
	Frame = 0;			//フレーム初期化
	Count = 0;			//カウント初期化

	m_cDango.Init();	//団子初期化

	//プレイループへ
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//ロード
void PLAY::Load()
{
	for (int i = 0; i < 2; i++)
	{
		BackHandle[i] = LoadGraph("Data/Image/Play/BackPlay.png");	//背景読み込み
	}

	//文字
	TextHandle[0] = LoadGraph("Data/Image/Play/Finish.png");
	TextHandle[1] = LoadGraph("Data/Image/Play/Play.png");

	BGM = LoadSoundMem("Data/Sound/bgm.mp3");	//BGM読み込み
	SE = LoadSoundMem("Data/Sound/finish.wav");	//効果音読み込み

	m_cDango.Load();	//団子ロード
}

void PLAY::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);	//音量調整

	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, true);	//BGM再生
}

//通常処理
void PLAY::Step()
{
	for (int i = 0; i < 2; i++)
	{
		PosY[i]++;

		if (PosY[i] >= 720)
		{
			PosY[i] = -720;
		}
	}

	m_cDango.Step();	//団子ステップ	

	if (m_cDango.isClear)	//クリアフラグがtrueなら
	{
		if (!isSE)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, SE);
			PlaySoundMem(SE, DX_PLAYTYPE_BACK, true);
			isSE = true;
		}
		isDraw = true;	//描画フラグを立てる

		Fade += 5;

		Frame++;
		if (Frame >= FRAME_RATE)
		{
			Count++;
			Frame = 0;
		}

		if (Count >= 3)
		{
			//シーンフラグをリザルトシーンに変更
			m_SceneFlag = 0;

			//プレイ後処理へ移動
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

//描画処理
void PLAY::Draw()
{
	//背景
	DrawGraph(0, PosY[0], BackHandle[0], true);
	DrawTurnGraph(0, PosY[1], BackHandle[1], true);

	//文字
	DrawRotaGraph(720, 680, 2.0f, 0.0f, TextHandle[1], true);

	m_cDango.Draw();	//団子・串

	//文字
	if (isDraw)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
		DrawRotaGraph(640, 360, 1.0f, 0.0f, TextHandle[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//後処理
void PLAY::Fin()
{
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(BackHandle[i]);	//背景画像破棄
	}

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(TextHandle[i]);	//文字画像破棄
	}

	StopSoundMem(BGM);		//BGM停止
	DeleteSoundMem(BGM);	//BGM破棄
	
	StopSoundMem(SE);
	DeleteSoundMem(SE);

	m_cDango.Fin();		//団子後処理

	//リザルト初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
