#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"

int BackImage;	//タイトル背景画像ハンドル

int Start_BGM;	//BGMハンドル

void InitTitle()	//タイトル初期化
{
	BackImage = LoadGraph(BACK_PATH);	//タイトル背景画像読み込み

	Start_BGM = LoadSoundMem(START_BGM_PATH);	//BGM読み込み

	ChangeVolumeSoundMem(255 * 50 / 100, Start_BGM);	//BGMの音量を50%にする

	PlaySoundMem(Start_BGM, DX_PLAYTYPE_LOOP, true);	//BGM再生

	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;	//タイトルループへ移動
}

void StepTitle()	//タイトル通常処理
{
	if (IsKeyPush(KEY_INPUT_RETURN))	//Enterキーが押されたら
	{
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;	//タイトル後処理へ移動
	}
}

void DrawTitle()	//タイトル描画処理
{
	DrawGraph(0, 0, BackImage, true);	//タイトル背景画像描画
}

//タイトル後処理
void FinTitle()
{
	DeleteGraph(BackImage);	//タイトル背景画像破棄

	StopSoundMem(Start_BGM);	//BGM停止

	DeleteSoundMem(Start_BGM);	//BGM破棄

	g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//プレイシーンへ移動
}
