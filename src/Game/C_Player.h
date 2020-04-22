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


class C_Player :public GameObject {
public:
	C_Player();
	~C_Player();

	void Init()override;		//初期化用関数
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

	//プレイヤーの座標を外部に渡す関数
	const KdVec3& GetPlayerPos()const { return PlayerPos; }
	const float& GetCamAngY()	const { return CamAngY; }
	const bool& GetFeshFlg()	const { return FishFlg; }
	const bool& GetBuoiFlg()	const { return BuoiFlg; }

private:
	//----------関数宣言-------------
	void Begin();		//ゲーム起動時の初期化関数
	void End();

	void FlgProc();			//大本のフラグ管理用関数
	void MouseUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();

	void Draw3DWall();
	//---------行列-------------
	//固定変数
	KdVec3			InitPos = KdVec3(0.0f, 0.0f, 0.0f);		//初期位置
	KdVec3			InitCamPos = KdVec3(0.0f, 2.0f, 0.0f);
	S_CoordVec		CoordVec;

	float			CamAngX_LowLimit=-80;
	float			CamAngX_MaxLimit=40;
	float			CamAngY_LowLimit;
	float			CamAngY_MaxLimit;

	float			FSceneCamAngX_lowLimit = 0.0f;
	float			FSceneCamAngX_MaxLimit = 40.0f;
	float			FishScene_LenMax = 7.0f;
	float			FishScene_LenMin = 2.0f;

	KdVec3			PlayerPos;
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 2.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;

	//カメラ
	POINT				BasePt;
	KdVec3				CamLook;
	//---------変数宣言----------
	float				FishScene_StartPos = 4.0f;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.2f;
	float				FishScene_CamAngX = 0.0f;

	bool				FishFlg = false;
	bool				RestoreFlg = false;
	bool				BuoiFlg = false;		//浮きを動かすか否か

};