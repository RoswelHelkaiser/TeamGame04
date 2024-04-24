#pragma once
#include "../Scene.h"
#include "../../Player/Player.h"
#include "../../Transparent/Transparent.h"

const char RESULT_PATH[] = { "Data/Result/リザルト背景.png" };			//リザルトの画像パス
const char RESULT_MOJI_PATH[] = {"Data/Result/獲得コイン数 文字.png"};	//リザルト文字画像パス]
const char RESULT_NUMBER_PATH[] = { "Data/Result/number12x24_03.png" };
const char RESULT_BGM_PATH[] = { "Data/Sound/Result/PerituneMaterial_J_Result_Celtic_A.mp3" };

const int MOJI_X = 459 / 2;
const int MOJI_Y = 76 / 2;

const int UI_W_R = 6;
const int UI_H_R = 12;

const int SCORE_NUMBER_MAX_NUM = 13;

//リザルトクラス
class RESULT : public SCENE_BASE
{
private:
	//クラス宣言
	Player player;

	int ImageHandle;
	int MojiHandle;

	int m_moji_x;
	int m_moji_y;

	int score;
	int m_NumposX;
	int m_NumposY;
	int m_numberHandle[10];
	int m_UI_Image_posX;
	int m_UI_Image_posY;
	int num;
	int FreamCnt;
	int m_BgmHndl;

	int m_alpha;
	int m_Numalpha;

	bool IsMojiDraw;
	bool IsSceneFlag;			//シーン遷移できるかどうかのフラグ
	bool IsScoreDrawFrag;



public:

	//初期化
	void Init(int m_score);
	//ロード
	void Load() override;
	//音楽を流す
	void Sound();
	//通常処理
	void Step()	override;
	//描画処理
	void Draw() override;
	//後処理
	void Fin() override;

};