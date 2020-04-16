#pragma once
#include"../System/FrameBase/GameObject.h"



class Title: GameObject
{
public:
	Title();
	~Title();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

private:
	D3DXMATRIX mMat;//�^�C�g��
	LPDIRECT3DTEXTURE9 vTex;
	D3DXVECTOR3 mPos;

	D3DXMATRIX mMat2;//�G���^�[�L�[
	D3DXVECTOR3 mPos2;
	LPDIRECT3DTEXTURE9 vTex2;

	int alpha;
	
};

