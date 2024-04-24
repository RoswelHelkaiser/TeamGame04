#include "SceneResult.h"
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../Scene.h"

//初期化
void RESULT::Init(int m_score)
{

}
//ロード
void RESULT::Load()
{
}
void RESULT::Sound()
{
}

//通常処理
void RESULT::Step()
{
	
	//タイトルシーンへの遷移
	if (IsKeyPush(KEY_INPUT_RETURN) ){
		//シーンフラグをタイトルシーンに変更
		m_SceneFlag = 0;
		//リザルト後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}


}

//描画処理
void RESULT::Draw()
{

}

//後処理
void RESULT::Fin()
{

}