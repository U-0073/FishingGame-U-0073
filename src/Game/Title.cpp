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
	vTex = RESOURCE_MNG.GetTexture("Title.png");
	vTex2 = RESOURCE_MNG.GetTexture("PRESSENTER.png");


	mPos =  { 0.0f, 0.0f, 0.0f };
	mPos2 = { 0.0f, 0.0f, 0.0f };


	mMat.SetTrans(mPos);
	mMat2.SetTrans(mPos2);
}

void Title::Update()
{
	mPos = {628, 150, 0};
	mPos2 ={628, 600, 0};

	if (alpha > 255) {
		alpha -= 1;
		if (alpha == 0) {
			alpha = 0;
		}
	}
	else if (alpha < 0) {
		alpha += 1;
		if (alpha == 255) {
			alpha = 255;
		}
	}

	mMat.SetTrans(mPos);
	mMat2.SetTrans(mPos2);

}

void Title::Draw2D()
{
	RECT rcTitle = { 0,0,674,108 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(*vTex, &rcTitle, &D3DXVECTOR3(337.0f, 54.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcENTER = { 0,0,432,88 };
	SPRITE->SetTransform(&mMat2);
	SPRITE->Draw(*vTex2, &rcTitle, &D3DXVECTOR3(216.0f, 44.0f, 0.0f), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

void Title::Draw3D()
{
}

void Title::End()
{
	m_pModel = nullptr;
	vTex = nullptr;
	vTex2 = nullptr;
}

