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
	vTex = RESOURCE_MNG.GetTexture("Title.png", 674, 108, D3DCOLOR_ARGB(255, 255, 255, 255));
	vTex2 = RESOURCE_MNG.GetTexture("PRESSENTER.png", 432, 88, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	titleAnime = RESOURCE_MNG.GetTexture("U+0037logo.png");
	whiteAnime = RESOURCE_MNG.GetTexture("whiteBack.png");


	mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mPos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mMat2, 0.0f, 0.0f, 0.0f);
	animMat.CreateTrans(1280 / 2, 720 / 2, 0);
	wAnim.CreateTrans(0,0, 0);

	animAlpha = 0;
	animFlg = false;
}

void Title::Update()
{
	mPos = D3DXVECTOR3(628, 150, 0);
	mPos2 = D3DXVECTOR3(628, 600, 0);

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

	if (!animFlg) {
		animAlpha++;
		if (animAlpha > 255) {
			animAlpha = 255;
			animFlg = true;
		}
	}
	else {
		animAlpha--;
		if (animAlpha < 0) {
			animAlpha = 0;
		}
	}

	D3DXMatrixTranslation(&mMat, mPos.x, mPos.y, mPos.z);
	D3DXMatrixTranslation(&mMat2, mPos2.x, mPos2.y, mPos2.z);

}

void Title::Draw2D()
{
	RECT rcTitle = { 0,0,674,108 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(*vTex, &rcTitle, &D3DXVECTOR3(337.0f, 54.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcENTER = { 0,0,432,88 };
	SPRITE->SetTransform(&mMat2);
	SPRITE->Draw(*vTex2, &rcTitle, &D3DXVECTOR3(216.0f, 44.0f, 0.0f), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));


	RECT rcWhite = { 0,0,1280,720 };
	SPRITE->SetTransform(&wAnim);
	if (!animFlg) {
		SPRITE->Draw(*whiteAnime, &rcWhite, &D3DXVECTOR3(0, 0, 0.0f), NULL, D3DCOLOR_ARGB(255, 254, 255, 255));
	}
	else {
		SPRITE->Draw(*whiteAnime, &rcWhite, &D3DXVECTOR3(0, 0, 0.0f), NULL, D3DCOLOR_ARGB(animAlpha, 254, 255, 255));

	}
	
	RECT rcAnim = { 0,0,720,720 };
	SPRITE->SetTransform(&animMat);
	SPRITE->Draw(*titleAnime, &rcAnim, &D3DXVECTOR3(720 / 2, 720 / 2, 0.0f), NULL, D3DCOLOR_ARGB(animAlpha, 255, 254, 255));

}

void Title::Draw3D()
{
}

void Title::End()
{
	m_pModel = nullptr;
	vTex = nullptr;
	vTex2 = nullptr;

	titleAnime = nullptr;
	whiteAnime = nullptr;
	/*
	if (vTex != nullptr)vTex->Release();
	if (vTex2 != nullptr)vTex2->Release();
	*/
}

