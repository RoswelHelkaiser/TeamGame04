#pragma once

//エフェクトの種類(余裕があったらもっと増やしてもいいです)
enum EFFECT_TYPE
{
	EFFECT_TYPE_EXPLOSION = 0,		//爆発
	EFFECT_TYPE_RECOVERY,			//回復

	EFFECT_TYPE_NUM,
};

//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
void LoadEffect(EFFECT_TYPE type, int create_num);

//エフェクトの初期化
void InitEffect();

//エフェクト通常処理
void StepEffect();

//エフェクト描画処理
void DrawEffect();

//エフェクトの後処理
void FinEffect();

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y);
