#pragma once
#include "../Scene.h"
#include <math.h>
#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Collision/Collision.h"
#include "../../Input/Input.h"
#include "../Result/SceneResult.h"
#include "../../Effect/Effect.h"

//�v���C�V�[���N���X
class PLAY : public SCENE_BASE
{
private:
	//�N���X�錾
	RESULT m_result;

	int m_numhndl;

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
