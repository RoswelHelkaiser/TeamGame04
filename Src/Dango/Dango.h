#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

#define DANGO_MAX_NUM	(5)	//列ごとの団子の数
#define STICK_MAX_NUM	(7)	//串の本数(列の数)

enum DANGO_COLOR	//団子の色
{
	DANGO_NORMAL,	//基本色
	DANGO_RED,		//赤色
	DANGO_YELLOW,	//黄色
	DANGO_GREEN,	//緑色
	DANGO_BLUE,		//青色

	DANGO_NUM
};

const char Dango_Path[DANGO_NUM][100]
{
	"Data/Image/Play/Dango/Dango1.png",		//基本色
	"Data/Image/Play/Dango/Dango2.png",		//赤色
	"Data/Image/Play/Dango/Dango3.png",		//黄色
	"Data/Image/Play/Dango/Dango4.png",		//緑色
	"Data/Image/Play/Dango/Dango5.png",		//青色
};

//団子情報構造体
struct SDango
{
	int Handle;	//画像ハンドル
	int Color;	//団子の色
	float PosX, PosY;	//X座標,Y座標
	bool isSelect;		//選択フラグ
};

//串情報構造体
struct SStick
{
	int Handle;			//画像ハンドル
	float PosX, PosY;	//X座標,Y座標
};

//矢印情報構造体
struct SArrow
{
	int Handle;			//画像ハンドル
	float PosX, PosY;	//X座標,Y座標
	bool isDraw;		//描画フラグ
};

//団子クラス
class Dango
{
	private:
		SDango s_Dango[DANGO_MAX_NUM][STICK_MAX_NUM];	//団子情報構造体
		SStick s_Stick[STICK_MAX_NUM];	//串情報構造体
		SArrow s_Guide;					//ガイド情報構造体
		int FileReadData[DANGO_MAX_NUM][STICK_MAX_NUM] = { 0 };	//ファイルからのデータ
		int Sample;						//サンプル団子画像ハンドル
		int DangoHandle[DANGO_NUM];		//団子画像ハンドル(読み込み用)
		int CollectColor;	//集める団子の色
		int Match;			//一致している団子の数
		int CurrentRow;		//選択中の列
		int CurrentLine;	//選択中の行
		int Sound;			//効果音
		
	public:
		bool isClear;	//クリアフラグ

		//初期化
		void Init();
		//ロード
		void Load();
		//通常処理
		void Step();
		//描画処理
		void Draw();
		//後処理
		void Fin();
		//選択
		void Select();
};
