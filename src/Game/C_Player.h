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
	KdVec3			StartVec = KdVec3(0, 1, 0);		//�����ʒu

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
	bool				CursorFlg = false;

};