#pragma once
#include "../Scene.h"
#include "../../Dango/Dango.h"

//�v���C�V�[���N���X
class PLAY : public SCENE_BASE
{
	private:
		int m_numhndl;
		int BackHandle[2];	//�w�i�摜�n���h��
		int PosY[2];		//�w�i��Y���W
		int TextHandle[2];	//�����摜�n���h��
		int TextPosY[2];	//������Y���W
		int SwitchMove;		//�����̏㏸���~
		bool isDraw;		//�����`��t���O
		int Fade;			//�����x
		int BGM;			//BGM�n���h��
		int SE;				//���ʉ�
		bool isSE;			//���ʉ���炷�t���O
		int Frame;			//�t���[��
		int Count;			//�J�E���g
		Dango m_cDango;		//�c�q�N���X

	public:
		//������
		void Init() override;
		//���[�h
		void Load() override;
		//���y�𗬂�
		void Sound();
		//�ʏ폈��
		void Step()	override;
		//�`�揈��
		void Draw() override;
		//�㏈��
		void Fin() override;
};
