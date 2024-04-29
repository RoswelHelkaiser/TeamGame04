#include "SceneResult.h"

//������
void RESULT::Init()
{
	BackHandle = 0;	//�w�i�摜������

	for (int i = 0; i < 2; i++)
	{
		TextHandle[i] = 0;	//�����摜������
	}

	SwitchMove = 0;
	Frame = 0;

	for (int i = 0; i < 5; i++)
	{
		DangoHandle[i] = 0;
	}

	DangoIndex = 0;

	DangoPosX = 0.0f;

	DangoPosY = 0.0f;

	Gravity = 0.0f;

	BGM = 0;		//BGM������

	//���[�v���U���g�ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
//���[�h
void RESULT::Load()
{
	//�w�i�摜�ǂݍ���
	BackHandle = LoadGraph("Data/Image/Result/BackResult.png");

	//�����摜�ǂݍ���
	TextHandle[0] = LoadGraph("Data/Image/Result/Result.png");
	TextHandle[1] = LoadGraph("Data/Image/Result/Back.png");

	DangoHandle[0] = LoadGraph("Data/Image/Play/Dango/Dango1.png");	//��{�F
	DangoHandle[1] = LoadGraph("Data/Image/Play/Dango/Dango2.png");	//�ԐF
	DangoHandle[2] = LoadGraph("Data/Image/Play/Dango/Dango3.png");	//���F
	DangoHandle[3] = LoadGraph("Data/Image/Play/Dango/Dango4.png");	//�ΐF
	DangoHandle[4] = LoadGraph("Data/Image/Play/Dango/Dango5.png");	//�F

	DangoIndex = GetRand(4);

	DangoPosX = (float)GetRand(800) + 200.0f;

	DangoPosY = -150.0f;

	BGM = LoadSoundMem("Data/Sound/clear.mp3");	//BGM�ǂݍ���
}
void RESULT::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);	//���ʒ���

	PlaySoundMem(BGM, DX_PLAYTYPE_BACK, true);	//BGM�Đ�
}

//�ʏ폈��
void RESULT::Step()
{
	DangoPosY += Gravity;
	Gravity += 0.1f;

	if (DangoPosY >= 800)
	{
		DangoIndex = GetRand(4);
		DangoPosX = (float)GetRand(800) + 200.0f;
		DangoPosY = -150.0f;
		Gravity = 0;
	}

	//�^�C�g���V�[���ւ̑J��
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//�V�[���t���O���^�C�g���V�[���ɕύX
		m_SceneFlag = 0;
		//���U���g�㏈���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
}

//�`�揈��
void RESULT::Draw()
{
	//�w�i
	DrawGraph(0, 0, BackHandle, true);

	//�c�q
	DrawRotaGraph((int)DangoPosX, (int)DangoPosY, 1.0f, 0.0f, DangoHandle[DangoIndex], true);
	
	//����
	DrawRotaGraph(640, 250, 1.0f, 0.0f, TextHandle[0], true);
	DrawRotaGraph(640, 500, 1.0f, 0.0f, TextHandle[1], true);
}

//�㏈��
void RESULT::Fin()
{	
	DeleteGraph(BackHandle);	//�w�i�摜�j��

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(TextHandle[i]);	//�����摜�j��
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(DangoHandle[i]);
	}

	StopSoundMem(BGM);		//BGM��~
	DeleteSoundMem(BGM);	//BGM�j��

	//�^�C�g���������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
