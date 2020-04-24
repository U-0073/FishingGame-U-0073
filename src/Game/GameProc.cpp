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
	ringTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/Ring3.png");
	notesTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/ScaleRing.png");
	 ringMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	notesMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	scale = 2.0f;
	dist = 1.0f;
}

void CGameProc::Update()
{
	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (scale > 0.9 && scale < 1.1) {
			dist -= 0.1f;
		}
			scale = 2.0f;
	}

	scale -= 0.005f;
	if (scale < 0.0f) {
		scale = 2.0f;
	}
	
}

void CGameProc::Draw()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//固定枠
	RECT rc = { 0,0,500,500 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//ノーツ
	KdMatrix scaleMat;
	notesMat.CreateTrans(KdVec3(1280/2, 720/2, 0));
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


	SPRITE->End();
	//デバッグ文字
	rc = { 0,0,0,0 };
	char buf[100];
	sprintf_s(buf, sizeof(buf), "scale=%4.5f dist=%4.1f", scale,dist);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGameProc::End()
{
}
