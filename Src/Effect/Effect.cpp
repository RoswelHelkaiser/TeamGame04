#include "DxLib.h"
#include "Effect.h"
#include "../Common.h"

//一度に表示できるエフェクト最大数(仮置き)
#define EFFECT_MAX_NUM		(100)

//エフェクトのアニメ最大数(仮置き)
#define EFFECT_ANIME_MAX_NUM	(4)	

//エフェクト情報
struct EffectInfo
{
	EFFECT_TYPE Kind;							//エフェクトの種類
	int animeHandle[EFFECT_ANIME_MAX_NUM];		//画像ハンドル
	int x, y;									//座標
	bool isUse;									//使用フラグ
	int animeUsedNum;							//アニメ数
	int currentAnimeIndex;						//現在のアニメ番号
	float changeTime;							//１枚あたりの表示時間
	float currentAnimeTime;						//現在のアニメ時間
};

//エフェクト情報
EffectInfo effectInfo[EFFECT_MAX_NUM];

//エフェクトのファイルパス
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"Data/Effect/Explosion.png",	//爆発
	"Data/Effect/Recovery.png",		//回復
};

//各エフェクトのアニメ数
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	4,	//EFFECT_TYPE_EXPLOSION
	4,	//EFFECT_TYPE_RECOVERY
};

//各エフェクトの画像分割数 [0] = x, [1] = y
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 2, 2,},	//EFFECT_TYPE_EXPLOSION
	{ 2, 2,},	//EFFECT_TYPE_RECOVERY
};

//エフェクトの画像サイズ
const int effectImageSize[EFFECT_TYPE_NUM] =
{
	64,		//EFFECT_TYPE_EXPLOSION
	32,		//EFFECT_TYPE_RECOVERY
};

//各エフェクトのアニメ画像切り替え時間
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.05f,	//EFFECT_TYPE_EXPLOSION
	0.05f,	//EFFECT_TYPE_RECOVERY
};

//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	for (int createIndex = 0; createIndex < create_num; createIndex++)
	{
		for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
		{
			//読み込みしていないエフェクト情報を見つける
			//（ひとつ目の画像ハンドルがゼロなら読み込みされてない）
			if (effectInfo[effectIndex].animeHandle[0] == 0)
			{
				//画像を分割読み込み
				int success_flg = LoadDivGraph(effectFilePath[type],
					effectAnimeImgNum[type],
					effectImageSplitNum[type][0],
					effectImageSplitNum[type][1],
					effectImageSize[type],
					effectImageSize[type],
					effectInfo[effectIndex].animeHandle);

				//成功した
				if (success_flg == 0)
				{
					for (int i = 0; i < EFFECT_MAX_NUM; i++)
					{
						//アニメ数を格納
						effectInfo[effectIndex].animeUsedNum = effectAnimeImgNum[type];

						//１枚当たりの表示時間を設定
						effectInfo[effectIndex].changeTime = effectChageTime[type];

						//エフェクトの種類を設定
						effectInfo[effectIndex].Kind = type;

					}
				}

				//成否にかかわらず抜ける
				break;
			}
		}
	}
}

//エフェクトの初期化
void InitEffect()
{
	//すべてのエフェクト情報の変数をクリアする（ゼロにする）
	for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
	{
		effectInfo[effectIndex].x = 0;
		effectInfo[effectIndex].y = 0;
		effectInfo[effectIndex].animeUsedNum = 0;
		effectInfo[effectIndex].currentAnimeIndex = 0;
		effectInfo[effectIndex].currentAnimeTime = 0.0f;
		effectInfo[effectIndex].changeTime = 0.0f;
		effectInfo[effectIndex].isUse = false;
		for (int i = 0; i < EFFECT_ANIME_MAX_NUM; i++)
		{
			effectInfo[effectIndex].animeHandle[i] = 0;
		}
	}
}

//エフェクト通常処理
void StepEffect()
{
	for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
	{
		//使用中ならアニメ時間を経過させて、アニメ番号を更新する
		if (effectInfo[effectIndex].isUse)
		{
			//画像切り替わるに必要な時間経過したら
			if (effectInfo[effectIndex].currentAnimeTime >= effectInfo[effectIndex].changeTime)
			{
				//次の画像へ
				effectInfo[effectIndex].currentAnimeIndex++;

				//計測時間リセット
				effectInfo[effectIndex].currentAnimeTime = 0.0f;

				//次の画像がもし無いなら
				if (effectInfo[effectIndex].currentAnimeIndex >= effectInfo[effectIndex].animeUsedNum)
				{
					//使用中フラグをOFFに
					effectInfo[effectIndex].isUse = false;

					//以下の処理は不要
					continue;
				}
			}

			//時間更新
			effectInfo[effectIndex].currentAnimeTime += 1.0f / FRAME_RATE;
		}
	}
}

//エフェクト描画処理
void DrawEffect()
{
	for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
	{
		//使用中なら現在のアニメ番号で描画する
		if (effectInfo[effectIndex].isUse)
		{
			DrawRotaGraph(effectInfo[effectIndex].x,
						  effectInfo[effectIndex].y,
						  1.0, 0.0, effectInfo[effectIndex].animeHandle[effectInfo[effectIndex].currentAnimeIndex], true);
		}
	}
}

//エフェクトの後処理
void FinEffect()
{
	//すべてのエフェクトを削除する
	for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
	{
		//すべて削除する
		for (int animeIndex = 0; animeIndex < EFFECT_ANIME_MAX_NUM; animeIndex++)
		{

			//ゼロ以外なら削除する
			if (effectInfo[effectIndex].animeHandle[animeIndex] != 0)
			{
				//画像削除
				DeleteGraph(effectInfo[effectIndex].animeHandle[animeIndex]);

				//削除したらゼロを入れておく
				effectInfo[effectIndex].animeHandle[animeIndex] = 0;
			}
		}
	}
}

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	//未使用エフェクトを探して再生
	for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
	{
		//使用中なら以下行わない
		if (effectInfo[effectIndex].isUse)
		{
			continue;
		}

		//タイプが一致した
		if (effectInfo[effectIndex].Kind == type)
		{
			//座標設定
			effectInfo[effectIndex].x = x;
			effectInfo[effectIndex].y = y;

			//計測用の変数をクリア
			effectInfo[effectIndex].currentAnimeIndex = 0;
			effectInfo[effectIndex].currentAnimeTime = 0.0f;

			//使用中にする
			effectInfo[effectIndex].isUse = true;

			//抜ける
			break;
		}
	}

}
