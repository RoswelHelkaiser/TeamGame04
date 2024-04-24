#pragma once
#include "../Scene.h"
#include <math.h>
#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Collision/Collision.h"
#include "../../Input/Input.h"
#include "../Result/SceneResult.h"
#include "../../Effect/Effect.h"

//�v���C�V�[���摜����
const int PLAY_IMAGE_PATH_NUM = 4;
const int PLAY_SOUND_PATH_NUM = 5;

const char PLAY_BGM_PATH[PLAY_SOUND_PATH_NUM][256] =
{
	"Data/Sound/Play/PlayBGM.mp3",		//�v���C�V�[����BGM
	"Data/Sound/Play/coin04.mp3",		//�R�C���l��SE
	"Data/Sound/Play/damaged1.mp3",		//�_���[�WSE
	"Data/Sound/Play/recovery.mp3",		//��SE

};

//�v���C�V�[���p�X
const char PLAY_PATH[PLAY_IMAGE_PATH_NUM][256] =
{
	"Data/Play/BackGround.png",		//�w�i
	"Data/Play/BackGround2.png",		//�w�i�Q
	"Data/Play/coin.png",			//�R�C��

};

const char PLAY_SCENE_BGM[] = { "" };				//�v���C�V�[����BGM

//�v���C�V�[���N���X
class PLAY : public SCENE_BASE
{
private:
	//�N���X�錾
	RESULT m_result;

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

