#pragma once

#include"../System/FrameBase/GameObject.h"

// 頂点情報の定義
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

	void Init()override;		//初期化用関数
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

	//プレイヤーの座標を外部に渡す関数
	const KdVec3& GetPlayerVec()const { return PlayerVec; }
	const float& GetCamAngY()const { return CamAngY; }
	const bool& GetFeshFlg()const { return FishFlg; }
	const bool& GetBuoiFlg()const { return BuoiFlg; }

private:
	//----------関数宣言-------------
	void Start();		//ゲーム起動時の初期化関数
	void End();

	void PointUpdate();
	void MoveProc();
	void CameraProc();
	void CameraSet();

	void Draw3DWall();
	//---------行列-------------
	KdVec3			PlayerVec;
	KdVec3			StartVec = KdVec3(0.0f, 0.0f, 0.0f);		//初期位置
	KdVec3			FishScene_CamPos = KdVec3(0.0f, 2.0f, 0.0f);

	KdMatrix		TransMat;
	KdMatrix		PlayerRot;

	VERTEX2				vWall[4];
	KdMatrix			WallMat;
	float				_WallDis;

	//カメラ
	POINT				BasePt;
	KdVec3				CamLook;
	//---------変数宣言----------
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