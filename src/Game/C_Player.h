#pragma once

#include"../System/FrameBase/GameObject.h"

// ���_���̒�`
struct VERTEX2
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};

class C_Player :public GameObject {
public:
	C_Player();
	~C_Player();

	void Init()override;		//�������p�֐�
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

	//�v���C���[�̍��W���O���ɓn���֐�
	const KdVec3& GetPlayerPos()const { return PlayerPos; }
	const float& GetCamAngY()const { return CamAngY; }
	const bool& GetFeshFlg()const { return FishFlg; }
	const bool& GetBuoiFlg()const { return BuoiFlg; }

private:
	//----------�֐��錾-------------
	void Begin();		//�Q�[���N�����̏������֐�
	void End();

	void FlgProc();			//��{�̃t���O�Ǘ��p�֐�
	void MouseUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();

	void Draw3DWall();
	//---------�s��-------------
	KdVec3			PlayerPos;
	KdVec3			StartVec = KdVec3(0.0f, 0.0f, 0.0f);		//�����ʒu
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 2.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;

	//�J����
	POINT				BasePt;
	KdVec3				CamLook;
	//---------�ϐ��錾----------
	int					Cnt1 = 0;
	int					Cnt2 = 0;

	float				FishScene_StartPos = 4.0f;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.2f;
	float				FishScene_CamAngX = 0.0f;

	bool				FishFlg = false;
	bool				RestoreFlg = false;
	bool				BuoiFlg = false;		//�����𓮂������ۂ�
	
};