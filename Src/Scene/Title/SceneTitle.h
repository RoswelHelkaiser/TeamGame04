#pragma once
#include "../Scene.h"

//タイトルクラス
class TITLE : public SCENE_BASE 
{
	private:
		int ImageHandle[4];	//画像ハンドル
		int Fade;			//透明度
		int DangoHandle[5];	//団子画像ハンドル(読み込み用)
		int DangoIndex;		//団子の添え字
		float DangoPosX;	//団子のX座標
		float DangoPosY;	//団子のY座標
		float Gravity;		//重力
		int BGM;			//BGMハンドル

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
