#pragma once
#include "../Scene.h"

//リザルトクラス
class RESULT : public SCENE_BASE
{
	private:
		int BackHandle;		//背景画像ハンドル
		int TextHandle[2];	//文字画像ハンドル
		int SwitchMove;		//文字の動き
		int Frame;			//フレーム
		int DangoHandle[5];	//団子画像ハンドル(読み込み用)
		int DangoIndex;		//団子の添え字
		float DangoPosX;	//団子のX座標
		float DangoPosY;	//団子のY座標
		float Gravity;		//重力
		int BGM;			//BGMハンドル

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