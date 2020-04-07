#pragma once

#include"../System/FrameBase/GameObject.h"

class C_Player :public GameObject {
public:
	C_Player();
	~C_Player();

	void Init()override;		//初期化用関数
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

private:
	//----------関数宣言-------------
	void Start();		//ゲーム起動時の初期化関数
	void End();

	void PointUpdate();
	void MoveProc();
	void CameraProc();

	//---------行列-------------
	KdVec3			PlayerVec;
	KdVec3			StartVec;		//初期位置

	KdMatrix		TransMat;
	//カメラ
	POINT				BasePt;
	D3DXMATRIX			CamRot;		//カメラの向いてる方向だけを管理する行列

	//---------変数宣言----------
	int					test = 0;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.5f;
	bool				CursorFlg = false;

};