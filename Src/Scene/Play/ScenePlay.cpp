#pragma once

#include "ScenePlay.h"
#include "../../Common.h"

#define NUM_DANGO_PATH "Data/Dango/dango1"

//=============================
// �v���C�V�[��
//=============================

//������
void PLAY::Init()
{
	m_numhndl = 0;

	//�v���C���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//���[�h
void PLAY::Load()
{
	m_numhndl = LoadGraph(NUM_DANGO_PATH);
}

void PLAY::Sound()
{

}

//�ʏ폈��
void PLAY::Step()
{

	//if (flamecount > 60)
	//{
	//	//�V�[���t���O�����U���g�V�[���ɕύX
	//	m_SceneFlag = 0;
	//	//�v���C�㏈���ֈړ�
	//	g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	//}
}

//�`�揈��
void PLAY::Draw()
{
	DrawGraph(600, 600, m_numhndl, true);
}

//�㏈��
void PLAY::Fin()
{

}

