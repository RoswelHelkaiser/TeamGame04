#pragma once
#include "ScenePlay.h"

//=============================
// �v���C�V�[��
//=============================

//������
void PLAY::Init()
{
	for (int i = 0; i < 2; i++)
	{
		BackHandle[i] = 0;		//�w�i�摜������
	}

	for (int i = 0; i < 2; i++)
	{
		TextHandle[i] = 0;	//�����摜�n���h��
	}

	PosY[0] = 0;
	PosY[1] = -720;

	isDraw = false;

	Fade = 0;

	BGM = 0;			//BGM������
	SE = 0;				//���ʉ�������
	Frame = 0;			//�t���[��������
	Count = 0;			//�J�E���g������

	m_cDango.Init();	//�c�q������

	//�v���C���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//���[�h
void PLAY::Load()
{
	for (int i = 0; i < 2; i++)
	{
		BackHandle[i] = LoadGraph("Data/Image/Play/BackPlay.png");	//�w�i�ǂݍ���
	}

	//����
	TextHandle[0] = LoadGraph("Data/Image/Play/Finish.png");
	TextHandle[1] = LoadGraph("Data/Image/Play/Play.png");

	BGM = LoadSoundMem("Data/Sound/bgm.mp3");	//BGM�ǂݍ���
	SE = LoadSoundMem("Data/Sound/finish.wav");	//���ʉ��ǂݍ���

	m_cDango.Load();	//�c�q���[�h
}

void PLAY::Sound()
{
	ChangeVolumeSoundMem(255 * 40 / 100, BGM);	//���ʒ���

	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, true);	//BGM�Đ�
}

//�ʏ폈��
void PLAY::Step()
{
	for (int i = 0; i < 2; i++)
	{
		PosY[i]++;

		if (PosY[i] >= 720)
		{
			PosY[i] = -720;
		}
	}

	m_cDango.Step();	//�c�q�X�e�b�v	

	if (m_cDango.isClear)	//�N���A�t���O��true�Ȃ�
	{
		if (!isSE)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, SE);
			PlaySoundMem(SE, DX_PLAYTYPE_BACK, true);
			isSE = true;
		}
		isDraw = true;	//�`��t���O�𗧂Ă�

		Fade += 5;

		Frame++;
		if (Frame >= FRAME_RATE)
		{
			Count++;
			Frame = 0;
		}

		if (Count >= 3)
		{
			//�V�[���t���O�����U���g�V�[���ɕύX
			m_SceneFlag = 0;

			//�v���C�㏈���ֈړ�
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

//�`�揈��
void PLAY::Draw()
{
	//�w�i
	DrawGraph(0, PosY[0], BackHandle[0], true);
	DrawTurnGraph(0, PosY[1], BackHandle[1], true);

	//����
	DrawRotaGraph(720, 680, 2.0f, 0.0f, TextHandle[1], true);

	m_cDango.Draw();	//�c�q�E��

	//����
	if (isDraw)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
		DrawRotaGraph(640, 360, 1.0f, 0.0f, TextHandle[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//�㏈��
void PLAY::Fin()
{
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(BackHandle[i]);	//�w�i�摜�j��
	}

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(TextHandle[i]);	//�����摜�j��
	}

	StopSoundMem(BGM);		//BGM��~
	DeleteSoundMem(BGM);	//BGM�j��
	
	StopSoundMem(SE);
	DeleteSoundMem(SE);

	m_cDango.Fin();		//�c�q�㏈��

	//���U���g�������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
