#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"
#include "../Score/Score.h"

int ClearImage;	//クリア背景画像ハンドル

int CursorImage;	//矢印画像ハンドル

int CursorPosX;		//矢印画像Y座標

bool isContinue;	//コンテニューフラグ

bool isBackTitle;	//タイトルフラグ

int Clear_BGM;		//BGMハンドル

void InitClear()	//クリア初期化
{
	ClearImage = LoadGraph(BACK_CLEAR_PATH);	//クリア背景画像読み込み

	CursorImage = LoadGraph(CURSOR_PATH);	//矢印画像読み込み

	LoadScore(NUMBER_0);	//0読み込み
	LoadScore(NUMBER_1);	//1読み込み
	LoadScore(NUMBER_2);	//2読み込み
	LoadScore(NUMBER_3);	//3読み込み
	LoadScore(NUMBER_4);	//4読み込み
	LoadScore(NUMBER_5);	//5読み込み
	LoadScore(NUMBER_6);	//6読み込み
	LoadScore(NUMBER_7);	//7読み込み
	LoadScore(NUMBER_8);	//8読み込み
	LoadScore(NUMBER_9);	//9読み込み

	CursorPosX = 150;	//矢印の初期Y座標を設定

	isContinue = false;		//コンテニューフラグを折る

	isBackTitle = false;	//タイトルフラグを折る

	Clear_BGM = LoadSoundMem(CLEAR_BGM_PATH);	//BGM読み込み

	ChangeVolumeSoundMem(255 * 50 / 100, Clear_BGM);	//BGMの音量を50%にする

	PlaySoundMem(Clear_BGM, DX_PLAYTYPE_LOOP, true);	//BGM再生

	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;	//クリアループへ移動
}

void StepClear()	//クリア通常処理
{
	if (IsKeyPush(KEY_INPUT_A) || IsKeyPush(KEY_INPUT_LEFT))	//Aキーまたは左矢印キーが押されたら
	{
		if (CursorPosX == 650)	//「もういいかな」の隣なら
		{
			CursorPosX = 150;	//「もっかい！」の隣に移動する
		}
	}

	else if (IsKeyPush(KEY_INPUT_D) || IsKeyPush(KEY_INPUT_RIGHT))	//Dキーまたは右矢印キーが押されたら
	{
		if (CursorPosX == 150)	//「もっかい！」の隣なら
		{
			CursorPosX = 650;	//「もういいかな」の隣に移動する
		}
	}

	if (IsKeyPush(KEY_INPUT_RETURN))	//エンターキーを押すと
	{
		if (CursorPosX == 150)	//「もっかい！」の隣なら
		{
			isContinue = true;	//コンテニューフラグを立てる
		}

		else if (CursorPosX == 650)	//「もういいかな」の隣なら
		{
			isBackTitle = true;	//タイトルフラグを折る
		}

		g_CurrentSceneID = SCENE_ID_FIN_CLEAR;	//クリア後処理へ移動
	}
}

void DrawClear()	//クリア描画処理
{
	DrawGraph(0, 0, ClearImage, true);	//クリア背景画像描画

	DrawRotaGraph(CursorPosX, 625, 0.5f, 0.0f, CursorImage, true);	//矢印画像描画

	ScoreInfo* scoreInfo = GetScoreInfo();	//スコア情報取得
	int Score = scoreInfo->CurrentScore;	//スコアを仮置き変数に代入
	int count = 0;	//カウント用変数
	while(Score > 0)	//スコアが0より大きいなら
	{
		int num = Score % 10;	//数字の添え字を決める
		Score /= 10;	//スコアを10で割る
		DrawGraph(665 - count * 50, 360, scoreInfo->ScoreHandle[num], true);
		count++;	//カウントを増やす
	}
}

void FinClear()	//クリア後処理
{
	ScoreInfo* scoreInfo = GetScoreInfo();	//スコア情報取得

	DeleteGraph(ClearImage);	//クリア背景画像破棄

	DeleteGraph(CursorImage);	//矢印画像破棄

	StopSoundMem(Clear_BGM);	//BGM停止

	DeleteSoundMem(Clear_BGM);	//BGM破棄

	for (int i = 0; i < NUMBER_NUM; i++)
	{
		DeleteGraph(scoreInfo->ScoreHandle[i]);	//数字画像破棄
	}

	if (isContinue)	//コンテニューフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//プレイシーンに戻る
	}

	else if (isBackTitle)	//タイトルフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_TITLE;	//タイトルシーンに戻る
	}
}