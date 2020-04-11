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
	//プレイヤーの座標を取ってくる関数
	KdVec3* GetPlayerPos() { return &PlayerVec; }

private:
	//----------関数宣言-------------
	void Start();		//ゲーム起動時の初期化関数
	void End();

	void PointUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();
	//---------行列-------------
	KdVec3			PlayerVec;
	KdVec3			StartVec = KdVec3(-121.0f, 5.0f, 0.0f);		//初期位置
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 4.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;
	LPD3DXFONT lpFont;		// フォント

	//カメラ
	POINT				BasePt;
	KdVec3				CamLook;
	//---------変数宣言----------
	int					test = 0;
	float				CamAngY = 0.0f;
	float				CamAngX = 0.0f;
	float				MoveSpeed = 0.2f;
	float				FishScene_CamAngX = 0.0f;
	bool				FishFlg = false;
	bool				CntFlg = false;
};