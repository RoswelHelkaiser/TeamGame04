#include "SceneResult.h"
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"

//������
void RESULT::Init(int m_score)
{

	//���U���g���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
//���[�h
void RESULT::Load()
{
}
void RESULT::Sound()
{
}

//�ʏ폈��
void RESULT::Step()
{
	//�^�C�g���V�[���ւ̑J��
	if (IsKeyPush(KEY_INPUT_RETURN) && IsSceneFlag) {
		//�V�[���t���O���^�C�g���V�[���ɕύX
		m_SceneFlag = 0;
		//���U���g�㏈���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}


}

//�`�揈��
void RESULT::Draw()
{

}

//�㏈��
void RESULT::Fin()
{

}