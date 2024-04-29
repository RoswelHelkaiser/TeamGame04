#include "SceneResult.h"

//初期化
void RESULT::Init()
{
	BackHandle = 0;	//背景画像初期化

	for (int i = 0; i < 2; i++)
	{
		TextHandle[i] = 0;	//文字画像初期化
	}

	SwitchMove = 0;
	Frame = 0;

	for (int i = 0; i < 5; i++)
	{
		DangoHandle[i] = 0;
	}

	DangoIndex = 0;

	DangoPosX = 0.0f;

	DangoPosY = 0.0f;

	Gravity = 0.0f;

	BGM = 0;		//BGM初期化

	//ループリザルトへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
//ロード
void RESULT::Load()
{
	//背景画像読み込み
	BackHandle = LoadGraph("Data/Image/Result/BackResult.png");

	//文字画像読み込み
	TextHandle[0] = LoadGraph("Data/Image/Result/Result.png");
	TextHandle[1] = LoadGraph("Data/Image/Result/Back.png");

	DangoHandle[0] = LoadGraph("Data/Image/Play/Dango/Dango1.png");	//基本色
	DangoHandle[1] = LoadGraph("Data/Image/Play/Dango/Dango2.png");	//赤色
	DangoHandle[2] = LoadGraph("Data/Image/Play/Dango/Dango3.png");	//黄色
	DangoHandle[3] = LoadGraph("Data/Image/Play/Dango/Dango4.png");	//緑色
	DangoHandle[4] = LoadGraph("Data/Image/Play/Dango/Dango5.png");	//青色

	DangoIndex = GetRand(4);

	DangoPosX = (float)GetRand(800) + 200.0f;

	DangoPosY = -150.0f;

	BGM = LoadSoundMem("Data/Sound/clear.mp3");	//BGM読み込み
}
void RESULT::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);	//音量調整

	PlaySoundMem(BGM, DX_PLAYTYPE_BACK, true);	//BGM再生
}

//通常処理
void RESULT::Step()
{
	DangoPosY += Gravity;
	Gravity += 0.1f;

	if (DangoPosY >= 800)
	{
		DangoIndex = GetRand(4);
		DangoPosX = (float)GetRand(800) + 200.0f;
		DangoPosY = -150.0f;
		Gravity = 0;
	}

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
	//背景
	DrawGraph(0, 0, BackHandle, true);

	//団子
	DrawRotaGraph((int)DangoPosX, (int)DangoPosY, 1.0f, 0.0f, DangoHandle[DangoIndex], true);
	
	//文字
	DrawRotaGraph(640, 250, 1.0f, 0.0f, TextHandle[0], true);
	DrawRotaGraph(640, 500, 1.0f, 0.0f, TextHandle[1], true);
}

//後処理
void RESULT::Fin()
{	
	DeleteGraph(BackHandle);	//背景画像破棄

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(TextHandle[i]);	//文字画像破棄
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(DangoHandle[i]);
	}

	StopSoundMem(BGM);		//BGM停止
	DeleteSoundMem(BGM);	//BGM破棄

	//タイトル初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
