#pragma once
#include "../Scene.h"

//リザルトクラス
class RESULT : public SCENE_BASE
{
	private:
		int BackHandle;	//背景画像ハンドル

	public:
		//初期化
		void Init();
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