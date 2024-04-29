#include "Dango.h"

//������
void Dango::Init()
{
	//�c�q
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
	//��
	for (int i = 0; i < 7; i++)
	{
		s_Stick[i].Handle = 0;
		s_Stick[i].PosX = 0.0f;
		s_Stick[i].PosY = 0.0f;
	}
	//�K�C�h
	s_Guide.Handle = 0;
	s_Guide.PosX = 0.0f;
	s_Guide.PosY = 0.0f;
	s_Guide.isDraw = false;
	//�T���v���c�q
	Sample = 0;

	CollectColor = GetRand(4);	//�W�߂�c�q�̐F�������_���Ɏw��
	Match = 0;					//�c�q�̈�v����������
	isClear = false;			//�N���A�t���O��܂�
	CurrentRow = 0;				//�ŏ���1��ڂɂ���
	CurrentLine = 0;			//�ŏ���1�s�ڂɂ���
	Sound = 0;					//���ʉ�������
}

//���[�h
void Dango::Load()
{
	DangoHandle[0] = LoadGraph(Dango_Path[0]);	//��{�F
	DangoHandle[1] = LoadGraph(Dango_Path[1]);	//�ԐF
	DangoHandle[2] = LoadGraph(Dango_Path[2]);	//���F
	DangoHandle[3] = LoadGraph(Dango_Path[3]);	//�ΐF
	DangoHandle[4] = LoadGraph(Dango_Path[4]);	//�F

	//�c�q
	for(int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			//�F�������_���ɐݒ�
			int DangoColor = GetRand(4);
			//�摜�ǂݍ���
			s_Dango[Y_Index][X_Index].Handle = DangoHandle[DangoColor];
			//�F������������
			s_Dango[Y_Index][X_Index].Color = DangoColor;
			//���W�ݒ�
			s_Dango[Y_Index][X_Index].PosX = 160.0f * X_Index + 160.0f;
			s_Dango[Y_Index][X_Index].PosY = 525.0f - 82.0f * Y_Index;
			if (s_Dango[Y_Index][X_Index].Color == CollectColor)
			{
				Match++;
			}
		}		
	}
	//��
	for (int i = 0; i < 7; i++)
	{	//�摜�ǂݍ���
		s_Stick[i].Handle = LoadGraph("Data/Image/Play/Dango/Stick.png");
		//���W�ݒ�
		s_Stick[i].PosX = 160.0f * i + 160.0f;
		s_Stick[i].PosY = 360.0f;
	}
	//�K�C�h
	s_Guide.Handle = LoadGraph("Data/Image/Play/Guide.png");	
	s_Guide.PosX = 160.0f;
	s_Guide.PosY = 525.0f;
	s_Guide.isDraw = true;
	//�T���v���c�q
	Sample = DangoHandle[CollectColor];
	Sound = LoadSoundMem("Data/Sound/change.wav");
}

//�ʏ폈��
void Dango::Step()
{
	if (!isClear)
	{
		Select();	//�I��
	}

	//�S�Ă̒c�q�̐F����������	
	if (Match == DANGO_MAX_NUM * STICK_MAX_NUM)
	{
		isClear = true;		//�N���A�t���O�𗧂Ă�
	}
}

//�`�揈��
void Dango::Draw()
{
	//��
	for (int i = 0; i < 7; i++)
	{
		DrawRotaGraph((int)s_Stick[i].PosX, (int)s_Stick[i].PosY, 1.0f, 0.0f, s_Stick[i].Handle, true);
	}
	//�c�q
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			DrawRotaGraph((int)s_Dango[Y_Index][X_Index].PosX, (int)s_Dango[Y_Index][X_Index].PosY, 1.0f, 0.0f, s_Dango[Y_Index][X_Index].Handle, true);
		}
	}
	//�K�C�h
	//�`��t���O��true�Ȃ�
	if (s_Guide.isDraw)
	{
		DrawRotaGraph((int)s_Guide.PosX, (int)s_Guide.PosY, 1.0f, 0.0f, s_Guide.Handle, true);
	}
	//�T���v���c�q
	DrawRotaGraph(510, 675, 0.5f, 0.0f, Sample, true);
}

//�㏈��
void Dango::Fin()
{
	//�c�q�摜�j��
	for (int i = 0; i < DANGO_NUM; i++)
	{
		for (int j = 0; j < DANGO_MAX_NUM; j++)
		{
			DeleteGraph(s_Dango[i][j].Handle);
		}
	}
	//�c�q
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			DeleteGraph(FileReadData[Y_Index][X_Index]);
		}
	}
	//���摜�j��
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(s_Stick[i].Handle);
	}
	//�K�C�h�摜�j��
	DeleteGraph(s_Guide.Handle);
	//�T���v���c�q�摜�j��
	DeleteGraph(Sample);
	StopSoundMem(Sound);
	DeleteSoundMem(Sound);
}

//�I��
void Dango::Select()
{
	//�E�L�[�������ꂽ��
	if (IsKeyPush(KEY_INPUT_RIGHT))
	{
		CurrentRow++;	//���̗�Ɉړ�
	
		s_Guide.PosX += 160.0f;	//�K�C�h���E�ɓ�����

		//�E�[�܂œ��B������
		if (s_Guide.PosX >= 1120.0f)
		{
			//����ȏ�i�܂Ȃ��悤�ɂ���
			s_Guide.PosX = 1120.0f;
			CurrentRow = 6;
		}		
	}

	//���L�[�������ꂽ��
	else if (IsKeyPush(KEY_INPUT_LEFT))
	{
		CurrentRow--;	//�O�̗�Ɉړ�

		s_Guide.PosX -= 160.0f;	//�K�C�h�����ɓ�����

		//���[�܂œ��B������
		if (s_Guide.PosX <= 160.0f)
		{
			//����ȏ�i�܂Ȃ��悤�ɂ���
			s_Guide.PosX = 160.0f;
			CurrentRow = 0;
		}
	}

	//���L�[�������ꂽ��
	if (IsKeyPush(KEY_INPUT_DOWN))
	{
		CurrentLine--;	//���̍s�Ɉړ�
		
		s_Guide.PosY += 82.0f;	//�K�C�h�����ɓ�����

		//���[�܂œ��B������
		if (s_Guide.PosY >= 525.0f)
		{
			//����ȏ�i�܂Ȃ��悤�ɂ���
			s_Guide.PosY = 525.0f;
			CurrentLine = 0;
		}		
	}

	//��L�[�������ꂽ��
	else if (IsKeyPush(KEY_INPUT_UP))
	{
		CurrentLine++;	//��̍s�Ɉړ�

		s_Guide.PosY -= 82.0f;	//�K�C�h����ɓ�����

		//��[�܂œ��B������
		if (s_Guide.PosY <= 196.0f)
		{
			//����ȏ�i�܂Ȃ��悤�ɂ���
			s_Guide.PosY = 196.0f;
			CurrentLine = 4;
		}
	}

	//�G���^�[�L�[�������ꂽ��
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		ChangeVolumeSoundMem(255 * 55 / 100, Sound);
		PlaySoundMem(Sound, DX_PLAYTYPE_BACK, true);

		int CurrentColor = s_Dango[CurrentLine][CurrentRow].Color;	//�I�𒆂̒c�q�̐F���擾
		//�w�肳�ꂽ�F�̒c�q��������
		if (s_Dango[CurrentLine][CurrentRow].Color == CollectColor)
		{
			Match--;	//���𐔂����炷
		}
		int NextColor = CurrentColor + 1;	//���̐F�p�̕ϐ���p��
		//�F��񂪍Ō�܂œ��B������
		if (NextColor >= DANGO_NUM)
		{
			//�ŏ��̐F�ɖ߂�
			NextColor = 0;
		}
		s_Dango[CurrentLine][CurrentRow].Handle = DangoHandle[NextColor];	//�ϐ����摜�n���h���ɑ��
		s_Dango[CurrentLine][CurrentRow].Color = NextColor;		//�F�����X�V
		//�X�V��̐F���w�肳�ꂽ�F�Ȃ�
		if (s_Dango[CurrentLine][CurrentRow].Color == CollectColor)
		{
			Match++;	//���𐔂𑝂₷
		}
	}
}
