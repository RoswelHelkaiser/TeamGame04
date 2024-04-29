#pragma once
#include "../Scene.h"
#include "../../Dango/Dango.h"

//プレイシーンクラス
class PLAY : public SCENE_BASE
{
	private:
		int m_numhndl;
		int BackHandle[2];	//背景画像ハンドル
		int PosY[2];		//背景のY座標
		int TextHandle[2];	//文字画像ハンドル
		int TextPosY[2];	//文字のY座標
		int SwitchMove;		//文字の上昇下降
		bool isDraw;		//文字描画フラグ
		int Fade;			//透明度
		int BGM;			//BGMハンドル
		int SE;				//効果音
		bool isSE;			//効果音を鳴らすフラグ
		int Frame;			//フレーム
		int Count;			//カウント
		Dango m_cDango;		//団子クラス

	public:
		//初期化
		void Init() override;
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
