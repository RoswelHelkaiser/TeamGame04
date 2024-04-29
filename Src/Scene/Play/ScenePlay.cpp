#pragma once
#include "ScenePlay.h"

//=============================
// �v���C�V�[��
//=============================

//������
void PLAY::Init()
{
	BackHandle = 0;		//�w�i�摜������

	m_cDango.Init();	//�c�q������

	//�v���C���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//���[�h
void PLAY::Load()
{
	BackHandle = LoadGraph("Data/Image/Play/BackPlay.png");
	m_cDango.Load();	//�c�q���[�h
}

void PLAY::Sound()
{

}

//�ʏ폈��
void PLAY::Step()
{
	m_cDango.Step();	//�c�q�X�e�b�v

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//�V�[���t���O�����U���g�V�[���ɕύX
		m_SceneFlag = 0;

		//�v���C�㏈���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
}

//�`�揈��
void PLAY::Draw()
{
	DrawGraph(0, 0, BackHandle, true);	//�w�i
	m_cDango.Draw();	//�c�q�E��
}

//�㏈��
void PLAY::Fin()
{
	DeleteGraph(BackHandle);	//�w�i�摜�j��
	m_cDango.Fin();		//�c�q�㏈��

	//���U���g�������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
