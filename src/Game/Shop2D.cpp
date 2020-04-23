#include"../System/KdLibrary/KdLibrary.h"
#include"Shop2D.h"

Shop2D::Shop2D()
{
}

Shop2D::~Shop2D()
{
}

void Shop2D::Init()
{
	vTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/Title.png", D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);
}

void Shop2D::Update()
{

}

void Shop2D::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcTitle = { 0,0,674,108 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(337.0f, 54.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	SPRITE->End();
}

void Shop2D::Draw3D()
{
}