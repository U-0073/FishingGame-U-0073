#pragma once
#include"../System/FrameBase/GameObject.h"

#define LISTNUMBER 8

class Shop2D : GameObject
{
public:
	Shop2D();
	~Shop2D();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

	int SetListChange();

private:
	D3DXMATRIX FrameMat,fTextMat,TabLeftMat, TabCenterMat, TabRightMat,ListSelectMat;
	LPDIRECT3DTEXTURE9 FrameTex,fTextTex, TabLeftTex, TabCenterTex, TabRightTex, ListSelectTex;

	D3DXMATRIX FrameSecMat,fTextSecMat, FrameSrdMat, fTextSrdMat;
	LPDIRECT3DTEXTURE9 FrameSecTex,fTextSecTex, FrameSrdTex, fTextSrdTex;
	
	D3DXMATRIX BaitMat[LISTNUMBER];
	LPDIRECT3DTEXTURE9 BaitTex[LISTNUMBER];
	RECT rcBait[8];

	D3DXVECTOR3 mPos;

	int cursor = 0;
	int tabPattern = 0;

	float select[LISTNUMBER];
	float tabL, tabC, tabR;

	bool KeyDownFlg = false, KeyUpFlg = false;
	bool KeyLeftFlg = false, KeyRightFlg = false;
	bool RodTextFlg = false, BaitTextFlg = false, ReelTextFlg = false;
};

