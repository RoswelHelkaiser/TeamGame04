#include "Dango.h"

//初期化
void Dango::Init()
{
	//団子
	for (int i = 0; i < DANGO_NUM; i++)
	{
		for (int j = 0; j < DANGO_MAX_NUM; j++)
		{
			s_Dango[i][j].Handle= 0;
			s_Dango[i][j].Color = 0;
			s_Dango[i][j].PosX = 0.0f;
			s_Dango[i][j].PosY = 0.0f;
		}
	}
	//串
	for (int i = 0; i < 7; i++)
	{
		s_Stick[i].Handle = 0;
		s_Stick[i].PosX = 0.0f;
		s_Stick[i].PosY = 0.0f;
	}
	//ガイド
	s_Guide.Handle = 0;
	s_Guide.PosX = 0.0f;
	s_Guide.PosY = 0.0f;
	s_Guide.isDraw = false;
	//サンプル団子
	Sample = 0;

	CollectColor = GetRand(4);	//集める団子の色をランダムに指定
	Match = 0;					//団子の一致数を初期化
	isClear = false;			//クリアフラグを折る
	CurrentRow = 0;				//最初は1列目にする
	CurrentLine = 0;			//最初は1行目にする
	Sound = 0;					//効果音初期化
}

//ロード
void Dango::Load()
{
	DangoHandle[0] = LoadGraph(Dango_Path[0]);	//基本色
	DangoHandle[1] = LoadGraph(Dango_Path[1]);	//赤色
	DangoHandle[2] = LoadGraph(Dango_Path[2]);	//黄色
	DangoHandle[3] = LoadGraph(Dango_Path[3]);	//緑色
	DangoHandle[4] = LoadGraph(Dango_Path[4]);	//青色

	//団子
	for(int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			//色をランダムに設定
			int DangoColor = GetRand(4);
			//画像読み込み
			s_Dango[Y_Index][X_Index].Handle = DangoHandle[DangoColor];
			//色情報を持たせる
			s_Dango[Y_Index][X_Index].Color = DangoColor;
			//座標設定
			s_Dango[Y_Index][X_Index].PosX = 160.0f * X_Index + 160.0f;
			s_Dango[Y_Index][X_Index].PosY = 525.0f - 82.0f * Y_Index;
			if (s_Dango[Y_Index][X_Index].Color == CollectColor)
			{
				Match++;
			}
		}		
	}
	//串
	for (int i = 0; i < 7; i++)
	{	//画像読み込み
		s_Stick[i].Handle = LoadGraph("Data/Image/Play/Dango/Stick.png");
		//座標設定
		s_Stick[i].PosX = 160.0f * i + 160.0f;
		s_Stick[i].PosY = 360.0f;
	}
	//ガイド
	s_Guide.Handle = LoadGraph("Data/Image/Play/Guide.png");	
	s_Guide.PosX = 160.0f;
	s_Guide.PosY = 525.0f;
	s_Guide.isDraw = true;
	//サンプル団子
	Sample = DangoHandle[CollectColor];
	Sound = LoadSoundMem("Data/Sound/change.wav");
}

//通常処理
void Dango::Step()
{
	if (!isClear)
	{
		Select();	//選択
	}

	//全ての団子の色が揃ったら	
	if (Match == DANGO_MAX_NUM * STICK_MAX_NUM)
	{
		isClear = true;		//クリアフラグを立てる
	}
}

//描画処理
void Dango::Draw()
{
	//串
	for (int i = 0; i < 7; i++)
	{
		DrawRotaGraph((int)s_Stick[i].PosX, (int)s_Stick[i].PosY, 1.0f, 0.0f, s_Stick[i].Handle, true);
	}
	//団子
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			DrawRotaGraph((int)s_Dango[Y_Index][X_Index].PosX, (int)s_Dango[Y_Index][X_Index].PosY, 1.0f, 0.0f, s_Dango[Y_Index][X_Index].Handle, true);
		}
	}
	//ガイド
	//描画フラグがtrueなら
	if (s_Guide.isDraw)
	{
		DrawRotaGraph((int)s_Guide.PosX, (int)s_Guide.PosY, 1.0f, 0.0f, s_Guide.Handle, true);
	}
	//サンプル団子
	DrawRotaGraph(510, 675, 0.5f, 0.0f, Sample, true);
}

//後処理
void Dango::Fin()
{
	//団子画像破棄
	for (int i = 0; i < DANGO_NUM; i++)
	{
		for (int j = 0; j < DANGO_MAX_NUM; j++)
		{
			DeleteGraph(s_Dango[i][j].Handle);
		}
	}
	//団子
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			DeleteGraph(FileReadData[Y_Index][X_Index]);
		}
	}
	//串画像破棄
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(s_Stick[i].Handle);
	}
	//ガイド画像破棄
	DeleteGraph(s_Guide.Handle);
	//サンプル団子画像破棄
	DeleteGraph(Sample);
	StopSoundMem(Sound);
	DeleteSoundMem(Sound);
}

//選択
void Dango::Select()
{
	//右キーが押されたら
	if (IsKeyPush(KEY_INPUT_RIGHT))
	{
		CurrentRow++;	//次の列に移動
	
		s_Guide.PosX += 160.0f;	//ガイドを右に動かす

		//右端まで到達したら
		if (s_Guide.PosX >= 1120.0f)
		{
			//それ以上進まないようにする
			s_Guide.PosX = 1120.0f;
			CurrentRow = 6;
		}		
	}

	//左キーが押されたら
	else if (IsKeyPush(KEY_INPUT_LEFT))
	{
		CurrentRow--;	//前の列に移動

		s_Guide.PosX -= 160.0f;	//ガイドを左に動かす

		//左端まで到達したら
		if (s_Guide.PosX <= 160.0f)
		{
			//それ以上進まないようにする
			s_Guide.PosX = 160.0f;
			CurrentRow = 0;
		}
	}

	//下キーが押されたら
	if (IsKeyPush(KEY_INPUT_DOWN))
	{
		CurrentLine--;	//下の行に移動
		
		s_Guide.PosY += 82.0f;	//ガイドを下に動かす

		//下端まで到達したら
		if (s_Guide.PosY >= 525.0f)
		{
			//それ以上進まないようにする
			s_Guide.PosY = 525.0f;
			CurrentLine = 0;
		}		
	}

	//上キーが押されたら
	else if (IsKeyPush(KEY_INPUT_UP))
	{
		CurrentLine++;	//上の行に移動

		s_Guide.PosY -= 82.0f;	//ガイドを上に動かす

		//上端まで到達したら
		if (s_Guide.PosY <= 196.0f)
		{
			//それ以上進まないようにする
			s_Guide.PosY = 196.0f;
			CurrentLine = 4;
		}
	}

	//エンターキーが押されたら
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		ChangeVolumeSoundMem(255 * 55 / 100, Sound);
		PlaySoundMem(Sound, DX_PLAYTYPE_BACK, true);

		int CurrentColor = s_Dango[CurrentLine][CurrentRow].Color;	//選択中の団子の色を取得
		//指定された色の団子だったら
		if (s_Dango[CurrentLine][CurrentRow].Color == CollectColor)
		{
			Match--;	//正解数を減らす
		}
		int NextColor = CurrentColor + 1;	//次の色用の変数を用意
		//色情報が最後まで到達したら
		if (NextColor >= DANGO_NUM)
		{
			//最初の色に戻す
			NextColor = 0;
		}
		s_Dango[CurrentLine][CurrentRow].Handle = DangoHandle[NextColor];	//変数を画像ハンドルに代入
		s_Dango[CurrentLine][CurrentRow].Color = NextColor;		//色情報を更新
		//更新後の色が指定された色なら
		if (s_Dango[CurrentLine][CurrentRow].Color == CollectColor)
		{
			Match++;	//正解数を増やす
		}
	}
}
