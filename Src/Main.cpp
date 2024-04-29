//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Common.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Scene/Title/SceneTitle.h"
#include "Scene/Play/ScenePlay.h"
#include "Scene/Result/SceneResult.h"

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

//タイトルクラス宣言
TITLE title;
//プレイシーンクラス宣言
PLAY play;
//リザルトシーンクラス宣言
RESULT result;


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

	//マウスカーソルを表示する
	SetMouseDispFlag(true);
	
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
					title.Init();
					title.Load();
					title.Sound();

				}//SCENE_ID_INIT_TITLEの終わりの括弧
				break;

				case SCENE_ID_LOOP_TITLE:
				{
					//タイトル描画処理
					title.Draw();
					//タイトル通常処理
					title.Step();

				}//SCENE_ID_LOOP_TITLEの終わりの括弧
				break;

				case SCENE_ID_FIN_TITLE:
				{
					//タイトル後処理
					title.Fin();

				}//SCENE_ID_FIN_TITLEの終わりの括弧
				break;

				case SCENE_ID_INIT_PLAY:
				{
					//プレイ初期化  
					play.Init();
					play.Load();
					play.Sound();

				}//SCENE_ID_INIT_PLAYの終わりの括弧
				break;

				case SCENE_ID_LOOP_PLAY:
				{
					//プレイ描画処理
					play.Draw();
					//プレイ通常処理
					play.Step();

				}//SCENE_ID_LOOP_PLAYの終わりの括弧
				break;

				case SCENE_ID_FIN_PLAY:
				{
					//プレイ後処理
					play.Fin();

				}//SCENE_ID_FIN_PLAYの終わりの括弧
				break;

				case SCENE_ID_INIT_RESULT:
				{
					//リザルト初期化  
					result.Init();

					//リザルト読み込み
					result.Load();

					result.Sound();
				}
				break;

				case SCENE_ID_LOOP_RESULT:
				{
					//リザルト描画処理
					result.Draw();
					//リザルト通常処理
					result.Step();
				}
				break;

				case SCENE_ID_FIN_RESULT:
				{
					//リザルト後処理
					result.Fin();
				}
				break;

			}//シーン振り分けのswitch文終了

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
