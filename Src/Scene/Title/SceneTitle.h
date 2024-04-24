#pragma once
#include "../Scene.h"
#include "../../Player/Player.h"

const char TITLE_BGM[] = { "Data/Sound/Title/ks011.wav" };		//タイトル画面のBGM

//タイトルクラス
class TITLE : public SCENE_BASE 
{
private:
	int m_BackHndl;
	int m_GroundHndl;
	int m_TitleHndl;
	int m_EnterHndl;
	int m_BGMHndl;

	//地面のスライド用の変数
	int m_GroundPosX;
	int m_GroundMaxPosX;

	//エンターの点滅用の変数
	int m_blink;
	

public:
	Player c_player;

	//初期化
	void Init() override;
	//ロード
	void Load() override;
	//通常処理
	void Step()	override;
	//描画処理
	void Draw() override;
	//後処理
	void Fin() override;

	//音楽を流すだけの処理
	void Sound();

};

