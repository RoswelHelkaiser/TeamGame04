
#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Input/Input.h"
#include "../../Transparent/Transparent.h"
#include "../../Collision/Collision.h"
#include "../../Transparent/Transparent.h"

//画像読み込み
#define TITEL_BACK_PATH	"Data/Title/BackGround.png"
#define TITEL_GROUND_PATH "Data/Title/ground.png"
#define TITLE_PATH	"Data/Title/Title.png"
#define TITLE_ENTER_PATH "Data/Title/Enter.png"

//=============================
// タイトルシーン
//=============================

//初期化
void TITLE::Init()
{
	//ハンドルの初期化
	m_BackHndl = 0;			//背景
	m_GroundHndl = 0;		//地面
	m_TitleHndl = 0;		//タイトル名
	m_EnterHndl = 0;		//エンター
	m_BGMHndl = -1;			//タイトル画面BGM

	//地面のスライド用の変数の初期化
	m_GroundPosX = 0;
	m_GroundMaxPosX = 1280;

	//エンターの点滅用の変数の初期化
	m_blink = 0;
	
	//プレイヤー初期化
	c_player.Init();
	c_player.DefaultValue();

	//タイトルループへ
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//ロード
void TITLE::Load()
{
	m_BGMHndl = LoadSoundMem(TITLE_BGM);
	m_BackHndl = LoadGraph(TITEL_BACK_PATH);
	m_GroundHndl = LoadGraph(TITEL_GROUND_PATH);
	m_TitleHndl = LoadGraph(TITLE_PATH);
	m_EnterHndl = LoadGraph(TITLE_ENTER_PATH);

	//プレイヤーロード
	c_player.Load();
}

void TITLE::Sound()
{
	PlaySoundMem(m_BGMHndl, DX_PLAYTYPE_LOOP);
}

//通常処理
void TITLE::Step()
{
	
	//地面のスクロール
	m_GroundPosX -= 4;
	m_GroundMaxPosX -= 4;
	if (m_GroundPosX <= -1280) {
		m_GroundPosX = 1280;
	}
	if (m_GroundMaxPosX <= -1280) {
		m_GroundMaxPosX = 1280;
	}

	m_blink = Transparent(m_blink, 1);

	c_player.Step(0);

	//メインメニューシーンへの遷移
	//Enterキー押されたなら
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//シーンフラグをプレイシーンに変更
		m_SceneFlag = 0;
		//タイトル後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}

}

//描画処理
void TITLE::Draw()
{
	DrawGraph(0, 0, m_BackHndl, true);
	DrawGraph(m_GroundPosX, 500, m_GroundHndl, true);
	DrawGraph(m_GroundMaxPosX, 500, m_GroundHndl, true);
	DrawGraph(300, 50, m_TitleHndl, true);
	
	//点滅処理（エンター）
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blink);
	DrawGraph(370, 350, m_EnterHndl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, m_blink);

	c_player.Draw(0);

}

//消去処理
void TITLE::Fin()
{
	//削除
	DeleteSoundMem(m_BGMHndl);

	c_player.Fin();

	//SceneFlagが0の時
	if (m_SceneFlag == 0)
	{
		//INITへ移動
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;
	}
}

