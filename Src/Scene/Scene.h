#pragma once
#include "../Input/Input.h"
#include "../Collision/Collision.h"

//シーンIDの種類
enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//プレイ関連
	SCENE_ID_INIT_PLAY = 200,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//ゲームクリア関連
	SCENE_ID_INIT_RESULT = 300,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,
};

//現在のシーンID
extern SCENE_ID g_CurrentSceneID;
