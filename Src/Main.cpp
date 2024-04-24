//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Common.h"
#include "Scene/Scene.h"
#include "Scene/SceneTitle.h"
#include "Scene/ScenePlay.h"
#include "Scene/SceneClear.h"
#include "Scene/SceneGameOver.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720		// Y方向の画面サイズを指定

//フレームレート情報
struct FrameRateInfo
{
	int currentTime;	//現在の時間
	int lastFrameTime;	//前回のフレーム実行時の時間
	int count;			//フレームカウント用
	int calcFpsTime;	//FPSを計算した時間
	float fps;			//計測したFPS（表示用）
};

//フレームレート情報変数
FrameRateInfo frameRateInfo;

//FPS計算
void CalcFPS();

//FPS表示（デバッグ用）
void DrawFPS();

//現在のシーンID
int g_CurrentSceneID = SCENE_ID_INIT_TITLE;

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//入力初期化
	InitInput();
	
	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く


	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//システムに処理を返す

		//現在の時間を取得
		frameRateInfo.currentTime = GetNowCount();

		//最初のループなら、
		//現在の時間を、FPSの計算をした時間に設定
		if (frameRateInfo.calcFpsTime == 0.0f)
		{
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}

		//現在の時間が、前回のフレーム時より
		//1000/60ミリ秒（1/60秒）以上経過していたら処理を実行する
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME)
		{
			//フレーム実行時の時間を更新
			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			//フレーム数をカウント
			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化
			ClearDrawScreen();

			//入力ステップ
			StepInput();

			//マウスカーソルを表示状態にする
			SetMouseDispFlag(true);

			//-----------------------------------------
			//ここからゲームの本体を書くことになる
			//-----------------------------------------

			//シーンIDによって処理の振り分け
			switch (g_CurrentSceneID)
			{
				case SCENE_ID_INIT_TITLE:
				{
					//タイトル初期化
					InitTitle();

				}//SCENE_ID_INIT_TITLEの終わりの括弧
				break;

				case SCENE_ID_LOOP_TITLE:
				{
					//タイトル通常処理
					StepTitle();

					//タイトル描画処理
					DrawTitle();

				}//SCENE_ID_LOOP_TITLEの終わりの括弧
				break;

				case SCENE_ID_FIN_TITLE:
				{
					//タイトル後処理
					FinTitle();

				}//SCENE_ID_FIN_TITLEの終わりの括弧
				break;

				case SCENE_ID_INIT_PLAY:
				{
					//プレイシーン初期化
					InitPlay();

				}//SCENE_ID_INIT_PLAYの終わりの括弧
				break;

				case SCENE_ID_LOOP_PLAY:
				{
					//プレイシーン通常処理
					StepPlay();

					//プレイシーン描画処理
					DrawPlay();

				}//SCENE_ID_LOOP_PLAYの終わりの括弧
				break;

				case SCENE_ID_FIN_PLAY:
				{
					//プレイシーン後処理
					FinPlay();

				}//SCENE_ID_FIN_PLAYの終わりの括弧
				break;

				//クリアシーン(高松)
				case SCENE_ID_INIT_CLEAR:
				{
					//クリア画面初期化
					InitClear();

				}//SCENE_ID_INIT_CLEARの終わりの括弧
				break;

				case SCENE_ID_LOOP_CLEAR:
				{
					//クリア画面通常処理
					StepClear();

					//クリア画面描画処理
					DrawClear();

				}//SCENE_ID_LOOP_CLEARの終わりの括弧
				break;

				case SCENE_ID_FIN_CLEAR:
				{
					//クリア画面後処理
					FinClear();

				}//SCENE_ID_FIN_CLEARの終わりの括弧
				break;

				//ゲームオーバーシーン担当宮近
				case SCENE_ID_INIT_GAMEOVER:
				{
					//ゲームオーバー画面初期化
					InitGameOver();

				}//SCENE_ID_INIT_GAMEOVERの終わりの括弧
				break;

				case SCENE_ID_LOOP_GAMEOVER:
				{
					//ゲームオーバー画面通常処理
					StepGameOver();

					//ゲームオーバー画面描画処理
					DrawGameOver();

				}//SCENE_ID_LOOP_GAMEOVERの終わりの括弧
				break;

				case SCENE_ID_FIN_GAMEOVER:
				{
					//ゲームオーバー画面後処理
					FinGameOver();

				}//SCENE_ID_FIN_GAMEOVERの終わりの括弧
				break;

			}//シーン振り分けのswitch文の終わりの括弧

			//FPS計算
			CalcFPS();

			//FPS表示
			DrawFPS();

			//-----------------------------------------
			//ループの終わりに
			//フリップ関数
			ScreenFlip();

		}//フレームレートのif文の終わりの括弧

	}//メインループの終わりの括弧

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く


	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

//FPS計算
void CalcFPS()
{
	//前回のFPSを計算した時間からの経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//前回のFPSを計算した時間から
	//１秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPSを求める
		//理想の数値は 60000 / 1000 で 60 となる
		frameRateInfo.fps = frameCount / difTime;

		//フレームレートカウントをクリア
		frameRateInfo.count = 0;

		//FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS表示（デバッグ用）
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1175, 700, color, "FPS[%.2f]", frameRateInfo.fps);
}
