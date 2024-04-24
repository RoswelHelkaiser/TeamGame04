#pragma once

#include "ScenePlay.h"
#include "../../Common.h"

//=============================
// プレイシーン
//=============================

//初期化
void PLAY::Init()
{
	player.Init();				//プレイヤーの初期化処理
	player.DefaultValue();		//プレイヤーの初期値設定
	m_map.Init();				//マップ初期化
	effectInfo.InitEffect();	//エフェクト初期化

	//背景座標
	m_BG_x[0] = WINDOW_WIDTH/2;
	m_BG_x[1] = WINDOW_WIDTH + (WINDOW_WIDTH / 2);
	m_BG_y = WINDOW_HEIGHT/2;

	//背景移動量
	m_BG_move_x = 0;

	flamecount = 0;

	for (int i = 0; i < PLAY_SOUND_PATH_NUM; i++)
	{
		m_PlayBgmHndl[i] = -1;
	}

	//プレイループへ
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//ロード
void PLAY::Load()
{
	m_ImageHandle[0] = LoadGraph(PLAY_PATH[0]);			//プレイ背景
	m_ImageHandle[1] = LoadGraph(PLAY_PATH[1]);			//プレイ背景2
	m_ImageHandle[2] = LoadGraph(PLAY_PATH[2]);			//コイン
	
	effectInfo.LoadEffect(EFFECT_TYPE_SHINE, 3);		//エフェクトキラキラ
	effectInfo.LoadEffect(EFFECT_TYPE_RECOVERY, 3);		//エフェクト回復

	//コイン座標
	m_coin_x = 50;
	m_coin_y = 50;

	for (int i = 0; i < 10; i++) {
		LoadDivGraph(RESULT_NUMBER_PATH, SCORE_NUMBER_MAX_NUM, SCORE_NUMBER_MAX_NUM, 1, 12, 24, m_numberHandle, false);
	}

	player.Load();				//プレイヤーの読み込み

	//ｂｇｍ、SE 読み込み
	for (int i = 0; i < PLAY_SOUND_PATH_NUM; i++)
	{
		m_PlayBgmHndl[i] = LoadSoundMem(PLAY_BGM_PATH[i]);
	}
}

void PLAY::Sound()
{
	PlaySoundMem(m_PlayBgmHndl[0], DX_PLAYTYPE_LOOP);
}

//通常処理
void PLAY::Step()
{	
	//プレイヤーが生きている時だけ処理を行う死んだらストップ
	if (player.DeathPlayer() == false)
	{
		player.Step(1);				//プレイヤーの通常処理
		effectInfo.StepEffect();		//エフェクト通常処理

		//背景スクロール処理
		m_BG_x[0] -= PLAYER_SPEED;
		m_BG_x[1] -= PLAYER_SPEED;
		m_BG_move_x -= PLAYER_SPEED;

		if (m_BG_x[0] <= -(WINDOW_WIDTH / 2))
		{
			m_BG_x[0] = WINDOW_WIDTH + (WINDOW_WIDTH / 2);
		}
		else if (m_BG_x[1] <= -(WINDOW_WIDTH / 2))
		{
			m_BG_x[1] = WINDOW_WIDTH + (WINDOW_WIDTH / 2);
		}

		//マップの当たり判定
		MapCollision(-m_BG_move_x);

		//プレイヤーの座標を更新
		player.UpdatePos();
	}

	//プレイヤーが死亡したら
	if (player.DeathPlayer() == true)
	{
		flamecount++;

		if (flamecount > 60)
		{
			//シーンフラグをリザルトシーンに変更
			m_SceneFlag = 0;
			//プレイ後処理へ移動
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}

	//デバッグ(死亡できなかった時のため)=============================
	//リザルトシーンへの遷移
	//左シフト押されたなら
	if (IsKeyPush(KEY_INPUT_LSHIFT))
	{
		//シーンフラグをリザルトシーンに変更
		m_SceneFlag = 0;
		//プレイ後処理へ移動
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
	//===============================================================
}

//描画処理
void PLAY::Draw()
{
	//背景描画
	DrawRotaGraph(m_BG_x[0], m_BG_y, 1.0f, 0.0f, m_ImageHandle[0], true);
	DrawRotaGraph(m_BG_x[1], m_BG_y, 1.0f, 0.0f, m_ImageHandle[1], true);

	m_map.Draw(-m_BG_move_x);	//マップ描画

	player.Draw(1);				//プレイヤーの描画処理

	effectInfo.DrawEffect();

	//コイ描画
	DrawRotaGraph(m_coin_x, m_coin_y, 0.8f, 1.0f, m_ImageHandle[2], true);

	int count = 0;

	int ItemScore = 0;

	num = 0;

	//コイン枚数描画
	SetFontSize(36);
	//スコアがゼロの時
	if (m_CoinNum == 0) {
		DrawFormatString(m_coin_x + 50, m_coin_y - 20, GetColor(255, 255, 255),"X", true);
		DrawRotaGraph(m_coin_x + 150, m_coin_y, 1.8f, 0.0f, m_numberHandle[0], true);
	}
	ItemScore = m_CoinNum;
	//スコアがゼロ以上の時
	while (ItemScore > 0) {
		num = ItemScore % 10;
		ItemScore = ItemScore / 10;
		//コイン枚数描画
		DrawFormatString(m_coin_x + 50, m_coin_y - 20, GetColor(255, 255, 255), "X", true);
		DrawRotaGraph(m_coin_x - count * 25 + 150, m_coin_y, 1.8f, 0.0f, m_numberHandle[num], true);
		count++;
	}
	SetFontSize(16);

	//デバッグ
	SetFontSize(30);
	SetFontSize(16);
}

//後処理
void PLAY::Fin()
{
	for (int i = 0; i < PLAY_SOUND_PATH_NUM; i++)
	{
		DeleteSoundMem(m_PlayBgmHndl[i]);
	}

	//SceneFlagが0の時
	if (m_SceneFlag == 0)
	{
		//プレイINITへ移動
		g_CurrentSceneID = SCENE_ID_INIT_RESULT;
	}
}

//マップの当たり判定
void PLAY::MapCollision(int mapmove)
{
	//プレイヤー
	//Y方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			//ブロック以外は処理しない
			if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == MAPCHIP_NONE)
			{
				continue;
			}

			//どの方向に進んでいたかチェック
			bool dirArray[4] = { false,false,false,false };
			player.GetMoveDirection(dirArray);

			//矩形の当たり判定用のデータを準備
			//プレイヤーの情報
			int Ax = player.GetPosX() - 20;
			int Ay = player.GetPosY() - 10;
			int Aw = PLAYER_WIDTH * 2;
			int Ah = PLAYER_HEIGHT * 2;

			//オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE + 20 - mapmove;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE + 10;

			//Y方向のみに移動したと仮定した座標で当たり判定をチェックします
			Ay = player.GetNextPosY();
			Ax = player.GetNextPosX();

			//当たっているかチェック
			if (IsHitRect(Ax + mapmove, Ay, Aw, Ah, Bx + mapmove, By, Bw, Bh)) {

				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 7)
				{
					if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 8)
					{
						if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 9)
						{
							// 上方向の修正
							if (dirArray[0]) {
								// めり込み量を計算する
								int overlap = By + Bh - Ay;
								player.SetNextPosY(Ay + overlap);

								//天井についたら押し返す
								player.PlayerCeiling();

							}
							//下方向の修正
							if (dirArray[1]) {
								// めり込み量を計算する
								int overlap = Ay + Ah - By;
								player.SetNextPosY(Ay - overlap);

								//落下したら
								player.PlayerLanding();

							}
						}
					}
				}

				//コイン処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 7)
				{
					//エフェクト描画
					effectInfo.PlayEffect(EFFECT_TYPE_SHINE, mapIndexX * MAP_SIZE -10
						+ m_BG_move_x, mapIndexY * MAP_SIZE + 10);

					ChangeVolumeSoundMem(150, m_PlayBgmHndl[1]);
					PlaySoundMem(m_PlayBgmHndl[1], DX_PLAYTYPE_LOOP, true);	//コインSE
					StopSoundMem(m_PlayBgmHndl[1], true);

					m_map.CoinStep(mapIndexX, mapIndexY);

					m_CoinNum += 1;
					
				}
				//トラップ処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 8)
				{
					ChangeVolumeSoundMem(130, m_PlayBgmHndl[2]);
					PlaySoundMem(m_PlayBgmHndl[2], DX_PLAYTYPE_LOOP, true);	//コインSE
					StopSoundMem(m_PlayBgmHndl[2], true);

					player.TrapStep();
				}
				//ハート処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 9)
				{
					//エフェクト描画
					effectInfo.PlayEffect(EFFECT_TYPE_RECOVERY, mapIndexX * MAP_SIZE - 10
						+ m_BG_move_x, mapIndexY * MAP_SIZE + 10);

					ChangeVolumeSoundMem(200, m_PlayBgmHndl[3]);
					PlaySoundMem(m_PlayBgmHndl[3], DX_PLAYTYPE_LOOP, true);	//回復SE
					StopSoundMem(m_PlayBgmHndl[3], true);

					player.PlayerHeal();	//プレイヤー回復処理

					m_map.HeartStep(mapIndexX, mapIndexY);
				}
			}
		}
	}

	// X方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// ブロック以外は処理しない
			if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == MAPCHIP_NONE)
				continue;

			//どの方向に進んでいたかチェック
			bool dirArray[4] = { false,false,false,false };
			player.GetMoveDirection(dirArray);

			//プレイヤーの情報
			int Ax = player.GetPosX() - 20;
			int Ay = player.GetPosY() - 10;
			int Aw = PLAYER_WIDTH * 2;
			int Ah = PLAYER_HEIGHT * 2;

			//オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE + 20 - mapmove;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE + 10;

			//X方向のみに移動したと仮定した座標で当たり判定をチェック
			Ay = player.GetNextPosY();
			Ax = player.GetNextPosX();

			// 当たっているかチェック
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {

				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 7)
				{
					if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 8)
					{
						if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] != 9)
						{
							// 左方向の修正
							if (dirArray[2]) {
								// めり込み量を計算する
								int overlap = Bx + Bw - Ax;
								player.SetNextPosX(Ax + overlap);
							}

							// 右方向の修正
							if (dirArray[3]) {
								// めり込み量を計算する
								int overlap = Ax + Aw - Bx;
								player.SetNextPosX(Ax - overlap);
							}
						}
					}
				}

				//コイン処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 7)
				{
					//エフェクト描画
					effectInfo.PlayEffect(EFFECT_TYPE_SHINE, mapIndexX* MAP_SIZE - 10
						+ m_BG_move_x, mapIndexY* MAP_SIZE + 10);

					ChangeVolumeSoundMem(150, m_PlayBgmHndl[1]);
					PlaySoundMem(m_PlayBgmHndl[1], DX_PLAYTYPE_LOOP, true);	//コインSE
					StopSoundMem(m_PlayBgmHndl[1], true);

					m_map.CoinStep(mapIndexX, mapIndexY);

					m_CoinNum += 1;
				}
				//トラップ処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 8)
				{
					ChangeVolumeSoundMem(130, m_PlayBgmHndl[2]);
					PlaySoundMem(m_PlayBgmHndl[2], DX_PLAYTYPE_LOOP, true);	//コインSE
					StopSoundMem(m_PlayBgmHndl[2], true);

					player.TrapStep();
				}
				//ハート処理
				if (m_map.m_FileReadMapData[mapIndexY][mapIndexX] == 9)
				{
					//エフェクト描画
					effectInfo.PlayEffect(EFFECT_TYPE_RECOVERY, mapIndexX* MAP_SIZE - 10
						+ m_BG_move_x, mapIndexY* MAP_SIZE + 10);

					ChangeVolumeSoundMem(255, m_PlayBgmHndl[3]);
					PlaySoundMem(m_PlayBgmHndl[3], DX_PLAYTYPE_LOOP, true);	//回復SE
					StopSoundMem(m_PlayBgmHndl[3], true);

					player.PlayerHeal();	//プレイヤー回復処理

					m_map.HeartStep(mapIndexX, mapIndexY);
				}
			}
		}
	}
}


//コインセット
void PLAY::SetCoin(int num)
{
	m_CoinNum = num;
}
