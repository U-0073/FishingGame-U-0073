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
	ringTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/Ring.png", NULL);
	ringMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
}

void CGameProc::Update()
{
}

void CGameProc::Draw()
{
}

void CGameProc::End()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rc = { 0,0,600,600 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(300.0f, 300.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->End();
}
