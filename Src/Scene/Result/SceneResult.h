#pragma once
#include "../Scene.h"

//���U���g�N���X
class RESULT : public SCENE_BASE
{
	private:
		int BackHandle;		//�w�i�摜�n���h��
		int TextHandle[2];	//�����摜�n���h��
		int SwitchMove;		//�����̓���
		int Frame;			//�t���[��
		int DangoHandle[5];	//�c�q�摜�n���h��(�ǂݍ��ݗp)
		int DangoIndex;		//�c�q�̓Y����
		float DangoPosX;	//�c�q��X���W
		float DangoPosY;	//�c�q��Y���W
		float Gravity;		//�d��
		int BGM;			//BGM�n���h��

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