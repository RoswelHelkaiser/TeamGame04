#pragma once
#include "../Scene.h"
#include "../../Dango/Dango.h"

//プレイシーンクラス
class PLAY : public SCENE_BASE
{
	private:
		int m_numhndl;
		int BackHandle;	//背景画像ハンドル
		Dango m_cDango;	//団子クラス

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
