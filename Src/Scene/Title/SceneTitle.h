#pragma once
#include "../Scene.h"

//�^�C�g���N���X
class TITLE : public SCENE_BASE 
{
	private:
		int ImageHandle[4];	//�摜�n���h��
		int Fade;			//�����x
		int DangoHandle[5];	//�c�q�摜�n���h��(�ǂݍ��ݗp)
		int DangoIndex;		//�c�q�̓Y����
		float DangoPosX;	//�c�q��X���W
		float DangoPosY;	//�c�q��Y���W
		float Gravity;		//�d��
		int BGM;			//BGM�n���h��

	public:

	//������
	void Init() override;
	//���[�h
	void Load() override;
	//�ʏ폈��
	void Step()	override;
	//�`�揈��
	void Draw() override;
	//�㏈��
	void Fin() override;

	//���y�𗬂������̏���
	void Sound();
};
