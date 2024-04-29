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
	//���
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

//���[�h
void Dango::Load()
{
	DangoHandle[0] = LoadGraph(Dango_Path[0]);	//��{�F
	DangoHandle[1] = LoadGraph(Dango_Path[1]);	//�ԐF
	DangoHandle[2] = LoadGraph(Dango_Path[2]);	//���F
	DangoHandle[3] = LoadGraph(Dango_Path[3]);	//�ΐF
	DangoHandle[4] = LoadGraph(Dango_Path[4]);	//�F
	ReadFile();	//�t�@�C���ǂݍ���

	//�c�q
	for(int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		for (int X_Index = 0; X_Index < STICK_MAX_NUM; X_Index++)
		{
			int DangoColor = FileReadData[Y_Index][X_Index];

			//�摜�ǂݍ���
			s_Dango[Y_Index][X_Index].Handle = DangoHandle[DangoColor];
			//���W�ݒ�
			s_Dango[Y_Index][X_Index].PosX = 160.0f * X_Index + 160.0f;
			s_Dango[Y_Index][X_Index].PosY = 525.0f - 82.0f * Y_Index;
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
	//���
	for (int i = 0; i < 2; i++)
	{
		s_Arrow[0].Handle = LoadGraph("Data/Image/Play/Arrow1.png");	//�ԐF
		s_Arrow[1].Handle = LoadGraph("Data/Image/Play/Arrow2.png");	//���F
		s_Arrow[i].PosX = 160;
		s_Arrow[i].PosY = 45;
		s_Arrow[0].isDraw = true;
		s_Arrow[1].isDraw = false;
	}
}

//�ʏ폈��
void Dango::Step()
{
	Select();	//�I��
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
	//���
	for (int i = 0; i < 2; i++)
	{
		//�`��t���O��true�Ȃ�
		if (s_Arrow[i].isDraw)
		{
			DrawRotaGraph(s_Arrow[i].PosX, s_Arrow[i].PosY, 1.0f, 0.0f, s_Arrow[i].Handle, true);
		}
	}
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
	//���摜�j��
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(s_Arrow[i].Handle);
	}
}

//�t�@�C���ǂݍ���
void Dango::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, "Data/csv/Pattern1.csv", "r");

	int DangoIndexX = 0;
	int DangoIndexY = 0;

	while (true)
	{
		//���l������ǂݍ���
		fscanf_s(fp, "%d", &FileReadData[DangoIndexY][DangoIndexX]);
		DangoIndexX++;

		//�u,�v���΂����߂ɓǂݍ��݂����s
		char chara = fgetc(fp);

		//EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (chara == EOF)
		{
			break;
		}

		//���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (chara == '\n')
		{
			DangoIndexX = 0;
			DangoIndexY++;
		}
	}

	fclose(fp);
}

//�I��
void Dango::Select()
{
	//�E�L�[�������ꂽ��
	if (IsKeyPush(KEY_INPUT_RIGHT))
	{
		CurrentRow++;

		//���̏���擪���珇�Ԃɉ�
		for (int i = 0; i < 2; i++)
		{
			//�I���t���O��false�Ȃ�
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[i].PosX += 160;	//�����E�ɓ�����

				//�E�[�܂œ��B������
				if (s_Arrow[i].PosX >= 1120)
				{
					//����ȏ�i�܂Ȃ��悤�ɂ���
					s_Arrow[i].PosX = 1120;
					CurrentRow = 6;
				}
			}
		}
	}

	//���L�[�������ꂽ��
	else if (IsKeyPush(KEY_INPUT_LEFT))
	{
		CurrentRow--;

		//���̏���擪���珇�Ԃɉ�
		for (int i = 0; i < 2; i++)
		{
			//�I���t���O��false�Ȃ�
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[i].PosX -= 160;	//�������ɓ�����

				//���[�܂œ��B������
				if (s_Arrow[i].PosX <= 160)
				{
					//����ȏ�i�܂Ȃ��悤�ɂ���
					s_Arrow[i].PosX = 160;
					CurrentRow = 0;
				}
			}
		}
	}

	//���̏���擪���珇�Ԃɉ�
	for (int i = 0; i < 2; i++)
	{
		//�G���^�[�L�[�������ꂽ��
		if (IsKeyPush(KEY_INPUT_RETURN))
		{
			//�ǂ���̖����I���t���O��false�Ȃ�
			if (!s_Arrow[i].isSelect)
			{
				s_Arrow[0].isSelect = true;		//�ԐF�̖��̑I���t���O�𗧂Ă�
				s_Arrow[1].isSelect = false;	//���F�̖��̑I���t���O��܂�
				s_Arrow[1].PosX = 160;			//���F�̖���X���W�����[�ɂ���
				s_Arrow[1].isDraw = true;		//���F�̖��̕`��t���O�𗧂Ă�
				PickUp();	//�c�q�I��
				CurrentRow = 0;
			}

			//�ԐF�̖�󂾂��I���t���O��true�Ȃ�
			else if (s_Arrow[0].isSelect && !s_Arrow[1].isSelect)
			{
				s_Arrow[1].isDraw = false;		//���F�̖��̕`��t���O��܂�
				s_Arrow[1].isSelect = true;		//���F�̖��̑I���t���O�𗧂Ă�
				s_Arrow[0].PosX = 160;			//�ԐF�̖���X���W�����[�ɂ���
				s_Arrow[0].isSelect = false;	//�ԐF�̖��̑I���t���O��܂�
				Move();		//�c�q�ړ�
				Compare();	//���딻��
				CurrentRow = 0;
			}
		}
	}
}

//�c�q�I��
void Dango::PickUp()
{
	//�c�q
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		if (FileReadData[Y_Index][CurrentRow] == 5)
		{
			Y_Index_Top = Y_Index - 1;	//�ЂƂO�̃C���f�b�N�X����ԏ�Ƃ��đ��
			break;
		}
	}
	s_Dango[Y_Index_Top][CurrentRow].isSelect = true;
	PreRow = CurrentRow;
}

//�c�q�ړ�
void Dango::Move()
{
	//�c�q����擪�����
	for (int Y_Index = 0; Y_Index < DANGO_MAX_NUM; Y_Index++)
	{
		if (FileReadData[Y_Index][CurrentRow] == 5)
		{
			s_Dango[Y_Index][CurrentRow].PosX = s_Dango[Y_Index_Top][PreRow].PosX;
		}
	}
}

//�F�������Ă��邩����
void Dango::Compare()
{
	//�c�q����擪�����
	for (int Y_Index = 0; Y_Index < 4; Y_Index++)
	{
		if (s_Dango[Y_Index][CurrentRow].Handle == s_Dango[Y_Index_Top][CurrentRow].Handle)
		{
			CurrentScore++;
			break;
		}
	}
}