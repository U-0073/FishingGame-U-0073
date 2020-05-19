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
	KdMatrix ItemNameTextMat;
	KdMatrix ItemDesMat;
	KdMatrix TabLeftMat;
	KdMatrix TabCenterMat;
	KdMatrix TabRightMat;
	KdMatrix ListSelectMat;

	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameSecTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameSrdTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ItemNameTextTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ItemDesTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabLeftTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabCenterTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabRightTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ListSelectTex;


	KdMatrix BaitMat;
	std::shared_ptr<LPDIRECT3DTEXTURE9> BaitTex;
	
	D3DXVECTOR3 mPos;

	int cursor = 0;
	int tabPattern = 0;

	float select[LISTNUMBER];
	float tabL = 0, tabC = 0, tabR = 0;

	bool KeyDownFlg = false;
	bool KeyUpFlg = false;
	bool KeyRightFlg = false;
	bool KeyLeftFlg = false;
	bool RodTextFlg = false;
	bool BaitTextFlg = false;
	bool ReelTextFlg = false;
};

