#include "SceneTitle.h"

//=============================
// �^�C�g���V�[��
//=============================

//������
void TITLE::Init()
{
	for (int i = 0; i < 4; i++)
	{
		//�摜�n���h��������
		ImageHandle[i] = 0;
	}

	Fade = 0;

	for (int i = 0; i < 5; i++)
	{
		DangoHandle[i] = 0;
	}

	DangoIndex = 0;

	DangoPosX = 0.0f;

	DangoPosY = 0.0f;

	Gravity = 0.0f;

	BGM = 0;	//BGM������

	//���[�v�^�C�g���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//���[�h
void TITLE::Load()
{
	ImageHandle[0] = LoadGraph("Data/Image/Title/BackTitle.png");	//�w�i�̃n���h��
	ImageHandle[1] = LoadGraph("Data/Image/Title/Title.png");		//���C���^�C�g���̃n���h��
	ImageHandle[2] = LoadGraph("Data/Image/Title/SubTitle.png");	//�T�u�^�C�g���̃n���h��
	ImageHandle[3] = LoadGraph("Data/Image/Title/Start.png");		//�X�^�[�g�̃n���h��

	DangoHandle[0] = LoadGraph("Data/Image/Play/Dango/Dango1.png");	//��{�F
	DangoHandle[1] = LoadGraph("Data/Image/Play/Dango/Dango2.png");	//�ԐF
	DangoHandle[2] = LoadGraph("Data/Image/Play/Dango/Dango3.png");	//���F
	DangoHandle[3] = LoadGraph("Data/Image/Play/Dango/Dango4.png");	//�ΐF
	DangoHandle[4] = LoadGraph("Data/Image/Play/Dango/Dango5.png");	//�F

	DangoIndex = GetRand(4);

	DangoPosX = (float)GetRand(800) + 200.0f;

	DangoPosY = -150.0f;

	BGM = LoadSoundMem("Data/Sound/title.mp3");		//BGM�ǂݍ���
}

void TITLE::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);		//���ʒ���

	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, true);		//BGM�Đ�
}

//�ʏ폈��
void TITLE::Step()
{
	Fade += 3;

	if (Fade >= 255)
	{
		Fade = 255;
	}

	DangoPosY += Gravity;
	Gravity += 0.1f;

	if (DangoPosY >= 800)
	{
		DangoIndex = GetRand(4);
		DangoPosX = (float)GetRand(800) + 200.0f;
		DangoPosY = -150.0f;
		Gravity = 0;
	}

	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//�^�C�g���㏈���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//�`�揈��
void TITLE::Draw()
{
	//�w�i
	DrawGraph(0, 0, ImageHandle[0], true);

	//�c�q
	DrawRotaGraph((int)DangoPosX, (int)DangoPosY, 1.0f, 0.0f, DangoHandle[DangoIndex], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
	//���C���^�C�g��
	DrawRotaGraph(640, 150, 1.0f, 0.0f, ImageHandle[1], true);
	//�T�u�^�C�g��
	DrawRotaGraph(640, 350, 1.0f, 0.0f, ImageHandle[2], true);
	//�X�^�[�g
	DrawRotaGraph(640, 550, 1.0f, 0.0f, ImageHandle[3], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//��������
void TITLE::Fin()
{
	for (int i = 0; i < 4; i++)
	{
		//�摜�j��
		DeleteGraph(ImageHandle[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(DangoHandle[i]);
	}

	StopSoundMem(BGM);		//BGM��~
	DeleteSoundMem(BGM);	//BGM�j��

	//�v���C�������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

