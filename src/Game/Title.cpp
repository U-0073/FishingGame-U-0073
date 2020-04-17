#include"../System/KdLibrary/KdLibrary.h"
#include"Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Init()
{
	KD3D.LoadTexture(&vTex, "Resouce/Texture/Title.png", 674, 108, D3DCOLOR_ARGB(255, 255, 255, 255));
	KD3D.LoadTexture(&vTex2, "Resouce/Texture/PRESSENTER.png", 432, 88, D3DCOLOR_ARGB(255, 255, 255, 255));

	mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mPos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mMat2, 0.0f, 0.0f, 0.0f);
}

void Title::Update()
{
	mPos = D3DXVECTOR3(628, 150, 0);
	mPos2 = D3DXVECTOR3(628, 600, 0);

	if (alpha > 255) {
		alpha -=1;
		if (alpha == 0) {
			alpha = 0;
		}
	}else if (alpha < 0) {
		alpha +=1;
		if (alpha == 255) {
			alpha = 255;
		}
	}
	
	

	D3DXMatrixTranslation(&mMat, mPos.x, mPos.y, mPos.z);
	D3DXMatrixTranslation(&mMat2, mPos2.x, mPos2.y, mPos2.z);

}

void Title::Draw2D()
{

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcTitle = { 0,0,1500,216 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(500.0f,108.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcENTER = { 0,0,432,88 };
	SPRITE->SetTransform(&mMat2);
	SPRITE->Draw(vTex2, &rcTitle, &D3DXVECTOR3(216.0f, 44.0f, 0.0f), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	SPRITE->End();
}

void Title::Draw3D()
{
}

