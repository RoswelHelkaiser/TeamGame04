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
	//矢印
	for (int i = 0; i < 2; i++)
	{
		s_Arrow[i].Handle = 0;
		s_Arrow[i].PosX = 0;
		s_Arrow[i].PosY = 0;
		s_Arrow[i].isDraw = false;
		s_Arrow[i].isSelect = false;
	}

	CurrentRow = 0;
	Y_Index_Top = 0;
	isReadFile = true;
}

//ロード
void Dango::Load()
{
	DangoHandle[0] = LoadGraph(Dango_Path[0]);	//基本色
	DangoHandle[1] = LoadGraph(Dango_Path[1]);	//赤色
	DangoHandle[2] = LoadGraph(Dango_Path[2]);	//黄色
	DangoHandle[3] = LoadGraph(Dango_Path[3]);	//緑色
	DangoHandle[4] = LoadGraph(Dango_Path[4]);	//青色
	ReadFile();	//ファイル読み込み

	//団子
	for(int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			int DangoColor = FileReadData[Y_Index][X_Index];

			//画像読み込み
			s_Dango[Y_Index][X_Index].Handle = DangoHandle[DangoColor];
			//座標設定
			s_Dango[Y_Index][X_Index].PosX = 160.0f * X_Index + 160.0f;
			s_Dango[Y_Index][X_Index].PosY = 525.0f - 82.0f * Y_Index;
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
	//矢印
	for (int i = 0; i < 2; i++)
	{
		s_Arrow[0].Handle = LoadGraph("Data/Image/Play/Arrow1.png");	//赤色
		s_Arrow[1].Handle = LoadGraph("Data/Image/Play/Arrow2.png");	//黄色
		s_Arrow[i].PosX = 160;
		s_Arrow[i].PosY = 45;
		s_Arrow[0].isDraw = true;
		s_Arrow[1].isDraw = false;
	}
}

//通常処理
void Dango::Step()
{
	Select();	//選択
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
	//矢印
	for (int i = 0; i < 2; i++)
	{
		//描画フラグがtrueなら
		if (s_Arrow[i].isDraw)
		{
			DrawRotaGraph(s_Arrow[i].PosX, s_Arrow[i].PosY, 1.0f, 0.0f, s_Arrow[i].Handle, true);
		}
	}
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
	//矢印画像破棄
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(s_Arrow[i].Handle);
	}
}

//ファイル読み込み
void Dango::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, "Data/csv/Pattern1.csv", "r");

	int DangoIndexX = 0;
	int DangoIndexY = 0;

	while (true)
	{
		//数値部分を読み込む
		fscanf_s(fp, "%d", &FileReadData[DangoIndexY][DangoIndexX]);
		DangoIndexX++;

		//「,」を飛ばすために読み込みを実行
		char chara = fgetc(fp);

		//EOFの場合は読み込み終了
		if (chara == EOF)
		{
			break;
		}

		//改行コードの場合は保存先を変更する
		if (chara == '\n')
		{
			DangoIndexX = 0;
			DangoIndexY++;
		}
	}

	fclose(fp);
}

//選択
void Dango::Select()
{
	//右キーが押されたら
	if (IsKeyPush(KEY_INPUT_RIGHT))
	{
		CurrentRow++;

		//矢印の情報を先頭から順番に回す
		for (int i = 0; i < 2; i++)
		{
			//選択フラグがfalseなら
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[i].PosX += 160;	//矢印を右に動かす

				//右端まで到達したら
				if (s_Arrow[i].PosX >= 1120)
				{
					//それ以上進まないようにする
					s_Arrow[i].PosX = 1120;
					CurrentRow = 6;
				}
			}
		}
	}

	//左キーが押されたら
	else if (IsKeyPush(KEY_INPUT_LEFT))
	{
		CurrentRow--;

		//矢印の情報を先頭から順番に回す
		for (int i = 0; i < 2; i++)
		{
			//選択フラグがfalseなら
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[i].PosX -= 160;	//矢印を左に動かす

				//左端まで到達したら
				if (s_Arrow[i].PosX <= 160)
				{
					//それ以上進まないようにする
					s_Arrow[i].PosX = 160;
					CurrentRow = 0;
				}
			}
		}
	}

	//矢印の情報を先頭から順番に回す
	for (int i = 0; i < 2; i++)
	{
		//エンターキーが押されたら
		if (IsKeyPush(KEY_INPUT_RETURN))
		{
			//どちらの矢印も選択フラグがfalseなら
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[0].isSelect = true;		//赤色の矢印の選択フラグを立てる
				s_Arrow[1].isSelect = false;	//黄色の矢印の選択フラグを折る
				s_Arrow[1].PosX = 160;			//黄色の矢印のX座標を左端にする
				s_Arrow[1].isDraw = true;		//黄色の矢印の描画フラグを立てる
				PickUp();	//団子選択
				CurrentRow = 0;
			}

			//赤色の矢印だけ選択フラグがtrueなら
			else if (s_Arrow[0].isSelect && !s_Arrow[1].isSelect)
			{
				s_Arrow[1].isDraw = false;		//黄色の矢印の描画フラグを折る
				s_Arrow[1].isSelect = true;		//黄色の矢印の選択フラグを立てる
				s_Arrow[0].PosX = 160;			//赤色の矢印のX座標を左端にする
				s_Arrow[0].isSelect = false;	//赤色の矢印の選択フラグを折る
				Move();		//団子移動
				Compare();	//正誤判定
				CurrentRow = 0;
			}
		}
	}
}

//団子選択
void Dango::PickUp()
{
	//団子
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		if (FileReadData[Y_Index][CurrentRow] == 5)
		{
			Y_Index_Top = Y_Index - 1;	//ひとつ前のインデックスを一番上として代入
			break;
		}
	}
	s_Dango[Y_Index_Top][CurrentRow].isSelect = true;
	PreRow = CurrentRow;
}

//団子移動
void Dango::Move()
{
	//団子情報を先頭から回す
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		if (FileReadData[Y_Index][CurrentRow] == 5)
		{
			s_Dango[Y_Index][CurrentRow].PosX = s_Dango[Y_Index_Top][PreRow].PosX;
		}
	}
}

//色が揃っているか判定
void Dango::Compare()
{
	//団子情報を先頭から回す
	for (int Y_Index = 0; Y_Index < 4; Y_Index++)
	{
		if (s_Dango[Y_Index][CurrentRow].Handle == s_Dango[Y_Index_Top][CurrentRow].Handle)
		{
			CurrentScore++;
			break;
		}
	}
}