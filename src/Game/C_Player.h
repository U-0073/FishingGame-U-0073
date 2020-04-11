#pragma once

#include"../System/FrameBase/GameObject.h"

class C_Player :public GameObject {
public:
	C_Player();
	~C_Player();

	void Init()override;		//�������p�֐�
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;
	//�v���C���[�̍��W������Ă���֐�
	KdVec3* GetPlayerPos() { return &PlayerVec; }

private:
	//----------�֐��錾-------------
	void Start();		//�Q�[���N�����̏������֐�
	void End();

	void PointUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();
	//---------�s��-------------
	KdVec3			PlayerVec;
	KdVec3			StartVec = KdVec3(-121.0f, 5.0f, 0.0f);		//�����ʒu
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 4.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;
	LPD3DXFONT lpFont;		// �t�H���g

	//�J����
	POINT				BasePt;
	KdVec3				CamLook;
	//---------�ϐ��錾----------
	int					test = 0;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.2f;
	float				FishScene_CamAngX = 0.0f;
	bool				FishFlg = false;
	bool				CntFlg = false;
};