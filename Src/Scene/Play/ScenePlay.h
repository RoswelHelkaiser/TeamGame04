#pragma once
#include "../Scene.h"
#include <math.h>
#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Collision/Collision.h"
#include "../../Input/Input.h"
#include "../Result/SceneResult.h"
#include "../../Effect/Effect.h"

//プレイシーン画像枚数
const int PLAY_IMAGE_PATH_NUM = 4;
const int PLAY_SOUND_PATH_NUM = 5;

const char PLAY_BGM_PATH[PLAY_SOUND_PATH_NUM][256] =
{
	"Data/Sound/Play/PlayBGM.mp3",		//プレイシーンのBGM
	"Data/Sound/Play/coin04.mp3",		//コイン獲得SE
	"Data/Sound/Play/damaged1.mp3",		//ダメージSE
	"Data/Sound/Play/recovery.mp3",		//回復SE

};

//プレイシーンパス
const char PLAY_PATH[PLAY_IMAGE_PATH_NUM][256] =
{
	"Data/Play/BackGround.png",		//背景
	"Data/Play/BackGround2.png",		//背景２
	"Data/Play/coin.png",			//コイン

};

const char PLAY_SCENE_BGM[] = { "" };				//プレイシーンのBGM

//プレイシーンクラス
class PLAY : public SCENE_BASE
{
private:
	//クラス宣言
	RESULT m_result;

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

