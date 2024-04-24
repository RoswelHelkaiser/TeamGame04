#pragma once
#include "../Scene.h"

//タイトルクラス
class TITLE : public SCENE_BASE 
{
	private:
		int ImageHandle[4];	//画像ハンドル

	public:

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
