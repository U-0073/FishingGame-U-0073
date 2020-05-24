#pragma once
#include"../../System/FrameBase/CSceneBase.h"

class CGameProc;

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return GAME; };
	void End()override;
private:
	//�Œ�g
	std::shared_ptr<LPDIRECT3DTEXTURE9> ringTex = nullptr;
	KdMatrix ringMat;


	//�m�[�c
	std::shared_ptr<LPDIRECT3DTEXTURE9> notesTex = nullptr;
	KdMatrix notesMat;
	float scale;

	//���蕶��
	std::shared_ptr<LPDIRECT3DTEXTURE9> judgeTex = nullptr;
	std::shared_ptr<LPDIRECT3DTEXTURE9> resultTex = nullptr;
	KdMatrix judgeMat;

	std::shared_ptr<LPDIRECT3DTEXTURE9> backTex = nullptr;
	KdMatrix backMat;

	float speed;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	int judgeFlg;

	//�}�E�X�֘A
	POINT Mouse;
	KdVec3 clickPos;
	float len;
	bool Check;
	bool frameStopper;

	int MusicChoise;

	//����p�摜�̃|�W�V�����ݒ�p�֐�
	const void SetPos(const KdVec3& Vec) {
		judgeMat._41 = Vec.x;
		judgeMat._42 = Vec.y;
		judgeMat._43 = Vec.z;
	}


	KdVec3 score;
	const void SetScore(const int Excellent, const int Miss)
	{
	}


	//�X�R�A�`�F�b�J�[
	int clickCNT;
	int Excellent;
	int Miss;

	//���̋���
	std::string name;

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};