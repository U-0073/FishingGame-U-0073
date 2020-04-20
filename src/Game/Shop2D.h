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
	D3DXMATRIX mMat;//ƒ^ƒCƒgƒ‹
	LPDIRECT3DTEXTURE9 vTex;
	D3DXVECTOR3 mPos;
};

