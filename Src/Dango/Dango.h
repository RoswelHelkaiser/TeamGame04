#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

#define DANGO_MAX_NUM	(5)	//�񂲂Ƃ̒c�q�̐�
#define STICK_MAX_NUM	(7)	//���̖{��(��̐�)

enum DANGO_COLOR	//�c�q�̐F
{
	DANGO_NORMAL,	//��{�F
	DANGO_RED,		//�ԐF
	DANGO_YELLOW,	//���F
	DANGO_GREEN,	//�ΐF
	DANGO_BLUE,		//�F

	DANGO_NUM
};

const char Dango_Path[DANGO_NUM][100]
{
	"Data/Image/Play/Dango/Dango1.png",		//��{�F
	"Data/Image/Play/Dango/Dango2.png",		//�ԐF
	"Data/Image/Play/Dango/Dango3.png",		//���F
	"Data/Image/Play/Dango/Dango4.png",		//�ΐF
	"Data/Image/Play/Dango/Dango5.png",		//�F
};

//�c�q���\����
struct SDango
{
	int Handle;	//�摜�n���h��
	int Color;	//�c�q�̐F
	float PosX, PosY;	//X���W,Y���W
	bool isSelect;		//�I���t���O
};

//�����\����
struct SStick
{
	int Handle;			//�摜�n���h��
	float PosX, PosY;	//X���W,Y���W
};

//�����\����
struct SArrow
{
	int Handle;			//�摜�n���h��
	float PosX, PosY;	//X���W,Y���W
	bool isDraw;		//�`��t���O
};

//�c�q�N���X
class Dango
{
	private:
		SDango s_Dango[DANGO_MAX_NUM][STICK_MAX_NUM];	//�c�q���\����
		SStick s_Stick[STICK_MAX_NUM];	//�����\����
		SArrow s_Guide;					//�K�C�h���\����
		int FileReadData[DANGO_MAX_NUM][STICK_MAX_NUM] = { 0 };	//�t�@�C������̃f�[�^
		int Sample;						//�T���v���c�q�摜�n���h��
		int DangoHandle[DANGO_NUM];		//�c�q�摜�n���h��(�ǂݍ��ݗp)
		int CollectColor;	//�W�߂�c�q�̐F
		int Match;			//��v���Ă���c�q�̐�
		int CurrentRow;		//�I�𒆂̗�
		int CurrentLine;	//�I�𒆂̍s
		int Sound;			//���ʉ�
		
	public:
		bool isClear;	//�N���A�t���O

		//������
		void Init();
		//���[�h
		void Load();
		//�ʏ폈��
		void Step();
		//�`�揈��
		void Draw();
		//�㏈��
		void Fin();
		//�I��
		void Select();
};
