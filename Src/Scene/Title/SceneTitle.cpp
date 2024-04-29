#include "SceneTitle.h"

//=============================
// タイトルシーン
//=============================

//初期化
void TITLE::Init()
{
	for (int i = 0; i < 4; i++)
	{
		//画像ハンドル初期化
		ImageHandle[i] = 0;
	}

	Fade = 0;

	for (int i = 0; i < 5; i++)
	{
		DangoHandle[i] = 0;
	}

	DangoIndex = 0;

	DangoPosX = 0.0f;

	DangoPosY = 0.0f;

	Gravity = 0.0f;

	BGM = 0;	//BGM初期化

	//ループタイトルへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//ロード
void TITLE::Load()
{
	ImageHandle[0] = LoadGraph("Data/Image/Title/BackTitle.png");	//背景のハンドル
	ImageHandle[1] = LoadGraph("Data/Image/Title/Title.png");		//メインタイトルのハンドル
	ImageHandle[2] = LoadGraph("Data/Image/Title/SubTitle.png");	//サブタイトルのハンドル
	ImageHandle[3] = LoadGraph("Data/Image/Title/Start.png");		//スタートのハンドル

	DangoHandle[0] = LoadGraph("Data/Image/Play/Dango/Dango1.png");	//基本色
	DangoHandle[1] = LoadGraph("Data/Image/Play/Dango/Dango2.png");	//赤色
	DangoHandle[2] = LoadGraph("Data/Image/Play/Dango/Dango3.png");	//黄色
	DangoHandle[3] = LoadGraph("Data/Image/Play/Dango/Dango4.png");	//緑色
	DangoHandle[4] = LoadGraph("Data/Image/Play/Dango/Dango5.png");	//青色

	DangoIndex = GetRand(4);

	DangoPosX = (float)GetRand(800) + 200.0f;

	DangoPosY = -150.0f;

	BGM = LoadSoundMem("Data/Sound/title.mp3");		//BGM読み込み
}

void TITLE::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);		//音量調整

	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, true);		//BGM再生
}

//通常処理
void TITLE::Step()
{
	Fade += 3;

	if (Fade >= 255)
	{
		Fade = 255;
	}

	DangoPosY += Gravity;
	Gravity += 0.1f;

	if (DangoPosY >= 800)
	{
		DangoIndex = GetRand(4);
		DangoPosX = (float)GetRand(800) + 200.0f;
		DangoPosY = -150.0f;
		Gravity = 0;
	}

	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//タイトル後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//描画処理
void TITLE::Draw()
{
	//背景
	DrawGraph(0, 0, ImageHandle[0], true);

	//団子
	DrawRotaGraph((int)DangoPosX, (int)DangoPosY, 1.0f, 0.0f, DangoHandle[DangoIndex], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
	//メインタイトル
	DrawRotaGraph(640, 150, 1.0f, 0.0f, ImageHandle[1], true);
	//サブタイトル
	DrawRotaGraph(640, 350, 1.0f, 0.0f, ImageHandle[2], true);
	//スタート
	DrawRotaGraph(640, 550, 1.0f, 0.0f, ImageHandle[3], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//消去処理
void TITLE::Fin()
{
	for (int i = 0; i < 4; i++)
	{
		//画像破棄
		DeleteGraph(ImageHandle[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(DangoHandle[i]);
	}

	StopSoundMem(BGM);		//BGM停止
	DeleteSoundMem(BGM);	//BGM破棄

	//プレイ初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

