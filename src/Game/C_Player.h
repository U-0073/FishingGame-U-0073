#pragma once

#include"../System/FrameBase/GameObject.h"



struct S_CoordVec {
	KdVec3 Z = KdVec3(0.0f, 0.0f, 1.0f);
	KdVec3 Y = KdVec3(0.0f, 1.0f, 0.0f);
	KdVec3 Front = KdVec3(0.0f, 0.0f, 1.0f);
	KdVec3 Back = KdVec3(0.0f, 0.0f, -1.0f);
	KdVec3 Right = KdVec3(1.0f, 0.0f, 0.0f);
	KdVec3 Left = KdVec3(-1.0f, 0.0f, 0.0f);

};

// ���_���̒�`
struct VERTEX2
{
	D3DXVECTOR3 Pos;
	D3DCOLOR	Color;
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
	const float& GetCamAngY()	const { return CamAngY; }
	const bool& GetFeshFlg()	const { return FishFlg; }
	const bool& GetBuoiFlg()	const { return BuoiFlg; }

	void End();
private:
	//----------�֐��錾-------------

	void FlgProc();			//��{�̃t���O�Ǘ��p�֐�
	void MoveProc();
	void Move();
	void Earth();
	void CameraProc();
	void CameraSet();
	void MouseUpdate();

	void MoveRay(D3DXVECTOR3 Vec);	//�����蔻����܂߂��ړ�
	//---------�s��-------------
	//�Œ�ϐ�
	KdVec3			InitPos = KdVec3(0.0f, 0.0f, 0.0f);		//�����ʒu
	KdVec3			InitCamPos = KdVec3(0.0f, 2.0f, 0.0f);
	S_CoordVec		CoordVec;

	float			CamAngX_LowLimit = -80;
	float			CamAngX_MaxLimit = 40;
	float			CamAngY_LowLimit;
	float			CamAngY_MaxLimit;

	float			FSceneCamAngX_lowLimit = 0.0f;
	float			FSceneCamAngX_MaxLimit = 40.0f;
	float			FishScene_LenMax = 7.0f;
	float			FishScene_LenMin = 2.0f;

	std::shared_ptr<KdModel> CollisionModel = nullptr;

	KdVec3			PlayerPos;
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 2.0f, 0.0f);
	KdVec3			GravityVec = KdVec3(0.0f, 0.4f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;
	KdMatrix		CollisionMat;

	//�J����
	POINT				BasePt;
	KdVec3				CamLook;
	//---------�ϐ��錾----------
	float				FishScene_StartPos = 4.0f;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.1f;
	float				FishScene_CamAngX = 0.0f;
	float TextMeshDis;

	bool				FishFlg = false;
	bool				RestoreFlg = false;
	bool				BuoiFlg = false;		//�����𓮂������ۂ�
	bool				WallFlg = false;


};