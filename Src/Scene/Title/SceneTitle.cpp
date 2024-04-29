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
}

void TITLE::Sound()
{

}

//通常処理
void TITLE::Step()
{


}

//描画処理
void TITLE::Draw()
{
	//背景
	DrawGraph(0, 0, ImageHandle[0], true);
	//メインタイトル
	DrawRotaGraph(640, 150, 1.0f, 0.0f, ImageHandle[1], true);
	//サブタイトル
	DrawRotaGraph(640, 350, 1.0f, 0.0f, ImageHandle[2], true);
	//スタート
	DrawRotaGraph(640, 550, 1.0f, 0.0f, ImageHandle[3], true);

	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//タイトル後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//消去処理
void TITLE::Fin()
{
	for (int i = 0; i < 4; i++)
	{
		//画像破棄
		DeleteGraph(ImageHandle[i]);
	}

	//プレイ初期化へ移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

