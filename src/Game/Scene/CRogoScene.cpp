#include"../../System/KdLibrary/KdLibrary.h"
#include"CRogoScene.h"

void CRogoScene::Init()
{
	titleAnime = RESOURCE_MNG.GetTexture("U+0037logo.png");
	whiteAnime = RESOURCE_MNG.GetTexture("whiteBack.png");

	animMat.CreateTrans(1280 / 2, 720 / 2, 0);
	wAnim.CreateTrans(0, 0, 0);

	animAlpha = 0;
	animFlg = false;

	m_pSound = RESOURCE_MNG.GetSound("SoundLogo#1_soft");
	m_pSound->Playsound("SoundLogo#1_soft", true, false);

}

int CRogoScene::Update()
{

	if (!animFlg) {
		animAlpha++;
		if (animAlpha > 255) {
			animAlpha = 255;
			animFlg = true;
		}
	}
	else {
		FADE.Start(2.5);
		return TITLE;
	}
	/*if (GetKey('M') & 0x8000) {
		FADE.Start(2.5);
		return MAP;
	}*/

	return ROGO;
}

void CRogoScene::Draw2D()
{
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


void CRogoScene::End()
{
	titleAnime = nullptr;
	whiteAnime = nullptr;
	m_pSound->LDSB8->Stop();
}
