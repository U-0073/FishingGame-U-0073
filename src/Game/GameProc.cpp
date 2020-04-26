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
	ringTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Ring3.png");
	notesTex = *RESOURCE_MNG.GetTexture("Resource/Texture/ScaleRing.png");
	ringMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	notesMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	scale = 2.0f;
	dist = 1.0f;
	level = rand() % 10;
	speed = level * 0.005f;
	clickNum = 0;
}

void CGameProc::Update()
{
	if (clickNum < 10) {
		if (GetKey(VK_LBUTTON) & 0x8000) {
			//clickNum++;
			if (scale > 0.7 && scale < 1.0) {
				dist -= 1 - (level * 0.2);
				speed += 0.0015;
			}
			scale = 2.0f;
		}

		scale -= speed;
		if (scale < 0.0f) {
			scale = 2.0f;
		}
	}
}

void CGameProc::Draw()
{
	//固定枠
	RECT rc = { 0,0,500,500 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(150, 255, 255, 255));
	//ノーツ
	KdMatrix scaleMat;
	notesMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	if (scale > 0.7f && scale < 1.f) {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else{
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SPRITE->End();
	/*
	//デバッグ文字
	rc = { 0,0,0,0 };
	char buf[100];
	sprintf_s(buf, sizeof(buf), "scale=%4.5f dist=%4.1f", scale, dist);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rc = { 0,650,0,0 };
	sprintf_s(buf, sizeof(buf), "残りクリック回数：%d", 10-clickNum);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	*/
}

void CGameProc::End()
{
}
/*
	lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&lpSListener);

secondTest3D->SetPosition(10, 10, 10, DS3D_IMMEDIATE);//音源の位置
lpSListener->SetPosition(playerPos.x, playerPos.y, playerPos.z, DS3D_IMMEDIATE);//聞き手の位置

D3DXVECTOR3 camLookVec = playerLookPos - playerPos;
D3DXVec3Normalize(&camLookVec, &camLookVec);

lpSListener->SetOrientation(camLookVec.x, camLookVec.y, camLookVec.z, 0, 1, 0, DS3D_IMMEDIATE);
*/