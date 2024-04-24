#pragma once

#define BACK_PATH	("Data/TitleImage/BgTitle.png")	//タイトルの背景画像のパス

#define START_BGM_PATH	("Data/Sound/Music/TitleScreen.mp3")	//BGMのパス

void InitTitle();	//タイトル初期化

void StepTitle();	//タイトル通常処理

void DrawTitle();	//タイトル描画処理

void FinTitle();	//タイトル後処理
