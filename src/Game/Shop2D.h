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
	void End()override;

	int SetListChange();

private:

	KdMatrix FrameMat;
	//KdMatrix FrameSecMat;
	//KdMatrix FrameSrdMat;
	KdMatrix ItemNameTextMat;
	KdMatrix ItemDesFrameMat;
	KdMatrix TabLeftMat;
	KdMatrix TabCenterMat;
	KdMatrix TabRightMat;
	KdMatrix ListSelectMat;

	LPDIRECT3DTEXTURE9 FrameTex;
	LPDIRECT3DTEXTURE9 FrameSecTex;
	LPDIRECT3DTEXTURE9 FrameSrdTex;
	LPDIRECT3DTEXTURE9 ItemNameTextTex;
	LPDIRECT3DTEXTURE9 ItemDesFrameTex;
	LPDIRECT3DTEXTURE9 TabLeftTex;
	LPDIRECT3DTEXTURE9 TabCenterTex;
	LPDIRECT3DTEXTURE9 TabRightTex;
	LPDIRECT3DTEXTURE9 ListSelectTex;


	KdMatrix BaitMat;
	LPDIRECT3DTEXTURE9 BaitTex;
	
	D3DXVECTOR3 mPos;

	int cursor = 0;
	int tabPattern = 0;

	float select[LISTNUMBER];
	float tabL, tabC, tabR;

	bool KeyDownFlg = false;
	bool KeyUpFlg = false;
	bool KeyRightFlg = false;
	bool KeyLeftFlg = false;
	bool RodTextFlg = false;
	bool BaitTextFlg = false;
	bool ReelTextFlg = false;
};

