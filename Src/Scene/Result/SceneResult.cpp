#include "SceneResult.h"

//������
void RESULT::Init()
{
	BackHandle = 0;	//�w�i�摜������

	//���[�v���U���g�ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
//���[�h
void RESULT::Load()
{
	//�w�i�摜�ǂݍ���
	BackHandle = LoadGraph("Data/Image/Result/BackResult.png");
}
void RESULT::Sound()
{
}

//�ʏ폈��
void RESULT::Step()
{
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
	DrawGraph(0, 0, BackHandle, true);	//�w�i
}

//�㏈��
void RESULT::Fin()
{
	DeleteGraph(BackHandle);	//�w�i�摜�j��
	//�^�C�g���������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}