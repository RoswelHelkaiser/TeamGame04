#pragma once
#include "../Scene.h"
#include <math.h>
#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Collision/Collision.h"
#include "../../Input/Input.h"
#include "../Result/SceneResult.h"
#include "../../Effect/Effect.h"

//プレイシーンクラス
class PLAY : public SCENE_BASE
{
private:
	//クラス宣言
	RESULT m_result;

	int m_numhndl;

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
