#pragma once
#include "../Scene.h"

//���U���g�N���X
class RESULT : public SCENE_BASE
{
	private:
		int BackHandle;	//�w�i�摜�n���h��

	public:
		//������
		void Init();
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