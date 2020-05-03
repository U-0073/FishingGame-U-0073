#pragma once
#include"../System/FrameBase/GameObject.h"

class Shop2D : GameObject
{
public:
	Shop2D();
	~Shop2D();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

private:
	D3DXMATRIX FrameMat,TabLeftMat, TabCenterMat, TabRightMat,ListSelectMat;
	D3DXMATRIX ListMat[6];
	LPDIRECT3DTEXTURE9 FrameTex, TabLeftTex, TabCenterTex, TabRightTex, ListSelectTex;
	LPDIRECT3DTEXTURE9 ListTex[6];
	D3DXVECTOR3 mPos;

	int cursor = 0;
	int tabPattern = 0;

	float select[6];
	float tabL, tabC, tabR;

	bool KeyDownFlg = false, KeyUpFlg = false;
	bool KeyLeftFlg = false, KeyRightFlg = false;
};

