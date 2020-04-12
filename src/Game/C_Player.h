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
	const KdVec3& GetPlayerVec()const { return PlayerVec; }
	const float& GetCamAngY()const { return CamAngY; }
	const bool& GetFeshFlg()const { return FishFlg; }
	const bool& GetBuoiFlg()const { return BuoiFlg; }

private:
	//----------�֐��錾-------------
	void Start();		//�Q�[���N�����̏������֐�
	void End();

	void PointUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();

	void Draw3DWall();
	//---------�s��-------------
	KdVec3			PlayerVec;
	KdVec3			StartVec = KdVec3(0.0f, 0.0f, 0.0f);		//�����ʒu
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 2.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;

	VERTEX2				vWall[4];
	KdMatrix			WallMat;
	float				_WallDis;

	//�J����
	POINT				BasePt;
	KdVec3				CamLook;
	//---------�ϐ��錾----------
	int					test = 0;
	float				FishScene_StartPos = 4.0f;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.2f;
	float				FishScene_CamAngX = 0.0f;
	bool				FishFlg = false;
	bool				CntFlg = false;
	bool				BuoiFlg = false;
};