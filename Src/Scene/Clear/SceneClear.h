#pragma once

#define BACK_CLEAR_PATH	("Data/ClearImage/BgClear.png")		//クリアの背景画像のパス
#define CURSOR_PATH		("Data/ClearImage/Cursor.png")		//矢印画像のパス

#define CLEAR_BGM_PATH	("Data/Sound/Music/ResultScreen.mp3")	//BGMのパス

void InitClear();	//クリア初期化

void StepClear();	//クリア通常処理

void DrawClear();	//クリア描画処理

void FinClear();	//クリア後処理
