#include"../System/KdLibrary/KdLibrary.h"
#include"GameProc.h"

CGameProc::CGameProc()
{
}
CGameProc::~CGameProc()
{
}

void CGameProc::Init()
{
	ringTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/Ring.png");
	 ringMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	notesMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	scale = 2.0f;
}

void CGameProc::Update()
{
	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (scale > 0.9 && scale < 1.1) {

		}
	}

	scale -= 0.01f;
	if (scale < 0.0f) {
		scale = 2.0f;
	}
	
}

void CGameProc::Draw()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//ŒÅ’è˜g
	RECT rc = { 0,0,460,460 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(230.0f, 230.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//ƒm[ƒc
	KdMatrix scaleMat;
	notesMat.CreateTrans(KdVec3(1280/2, 720/2, 0));
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(230.0f, 230.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


	SPRITE->End();
}

void CGameProc::End()
{
}
