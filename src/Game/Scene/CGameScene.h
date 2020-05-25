#pragma once
#include"../../System/FrameBase/CSceneBase.h"

//default���l�}�W�b�N�i���o�Ԃ�
#define scaleInitialize 2.0f
#define scaleLimit 0.0f

#define EFReduction 0.0215f		//EveryFrameInitialize�A���t���[���k���p
#define clickInitialize 10
#define defLenInitialize 10000	//Len�̏����Ăяo��

#define ZEROreturn 0				//0����Đ��䂷��p�BNULL����_���Ȃ̂��H

//judge�֘A
#define judgeMin 0.5
#define judgeMax 1.0
#define Length 100
#define FishSuccess 0.6
enum judgeNum
{
	Default_judge,
	Excellent_judge,
	Miss_judge,
};

//music�֘A
#define MFInitialize 240		//MusicFrameInitialize�A�ȏ����t���[���Ăяo��
enum MusicChoiseNum
{
	PhantomA2,		//Phantom_Apartment_2
	DDCats,				//Dance_Dance_Cats
	GStage2	,			//Green_Stage_2
	ROTWind2,			//Ride_On_The_Wind_2
	START,				//START!!
	ROTWindSP,		//Ride_On_The_Wind
	MusicGenerally	//���y�̑���
};



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