#pragma once

#include"../System/FrameBase/GameObject.h"

class C_Player :public GameObject{
public:
	C_Player();
	~C_Player();

	void Init()override;		//初期化用関数
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

private:
	void Start();		//ゲーム起動時の初期化関数
	void End();

	KdVec3			PlayerVec;
	KdVec3			StartVec;		//初期位置

	int test=0;
};