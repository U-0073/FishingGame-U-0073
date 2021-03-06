#include"../../System/KdLibrary/KdLibrary.h"
#include"CRogoScene.h"

void CRogoScene::Init()
{
	titleAnime = RESOURCE_MNG.GetTexture("U+0037logo.png");
	whiteAnime = RESOURCE_MNG.GetTexture("whiteBack.png");

	animMat.SetTrans(1280 / 2, 720 / 2, 0);
	wAnim.SetTrans(0, 0, 0);

	animAlpha = 0;
	animFlg = false;//���Ƃ���false

	m_pSound = RESOURCE_MNG.GetSound("Archievement_Jingle");
	m_pSound->Playsound("Archievement_Jingle", true, false);
	m_pSound->SetVol(0.8f);
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
		FADE.Start(5);//fade5->0.5
		return TITLE;
	}

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
