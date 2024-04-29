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
}

void TITLE::Sound()
{

}

//�ʏ폈��
void TITLE::Step()
{


}

//�`�揈��
void TITLE::Draw()
{
	//�w�i
	DrawGraph(0, 0, ImageHandle[0], true);
	//���C���^�C�g��
	DrawRotaGraph(640, 150, 1.0f, 0.0f, ImageHandle[1], true);
	//�T�u�^�C�g��
	DrawRotaGraph(640, 350, 1.0f, 0.0f, ImageHandle[2], true);
	//�X�^�[�g
	DrawRotaGraph(640, 550, 1.0f, 0.0f, ImageHandle[3], true);

	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//�^�C�g���㏈���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//��������
void TITLE::Fin()
{
	for (int i = 0; i < 4; i++)
	{
		//�摜�j��
		DeleteGraph(ImageHandle[i]);
	}

	//�v���C�������ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

