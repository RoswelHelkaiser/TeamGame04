#pragma once
#include "../Scene.h"
#include "../../Dango/Dango.h"

//�v���C�V�[���N���X
class PLAY : public SCENE_BASE
{
	private:
		int m_numhndl;
		int BackHandle;	//�w�i�摜�n���h��
		Dango m_cDango;	//�c�q�N���X

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
