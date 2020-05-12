#include"../System/KdLibrary/KdLibrary.h"
#include "CGameScene.h"
#include"GameProc.h"

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{
	if (ringTex != nullptr)ringTex->Release();
	if (notesTex != nullptr)notesTex->Release();
	if (backTex != nullptr) backTex->Release();
}

void CGameScene::Init()
{
	ringTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Ring4.png");
	notesTex = *RESOURCE_MNG.GetTexture("Resource/Texture/ScaleRing2.png");
	backTex = *RESOURCE_MNG.GetTexture("Resource/Texture/SeaBack002.png");

	ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
	notesMat = ringMat;
	backMat.CreateTrans(1280 / 2, 720 / 2, 0);
	//拡縮サイズ
	scale = 2.0f;
	//Lv1～5
	//level = rand() % 6 + 1;
	level = 5;
	speed = 0.01f;
	clickNum = 10;
	frame = 120;

	m_pSound = RESOURCE_MNG.GetSound("Resource/Sound/wave3.wav");
	m_pSound->Playsound("Resource/Sound/wave3.wav", true, true);

}

int CGameScene::Update()
{
	frame--;

	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (!keyFlg) {
			SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));

				//グレート（外側）の時の処理
				if (scale > 0.35 && scale < 0.7) {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/great.png");
				}
				//エクセレント（内側）の時の処理
				else if (scale > 0.0 && scale < 0.35) {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/excellent1.png");
				}
				//ミスの時の処理
				else {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/miss.png");
				}
				keyFlg = true;
				clickNum--;
				scale = 2.0f;
				ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
				notesMat = ringMat;

			}
		judgeFlg = true;
	}
	else { 
		keyFlg = false; 
		judgeFlg = false;
	}


	scale -= speed;
	if (scale < 0.0f) {
		scale = 2.0f;
	}

	//デバッグ用回避手段
	if (clickNum <= 0) {
		FADE.Start(5);
		return TITLE;
	}

	return GAME;
}

void CGameScene::Draw2D()
{
	//背景
	RECT rc = { 0,0,1280,720 };
	SPRITE->SetTransform(&backMat);
	SPRITE->Draw(backTex, &rc, &D3DXVECTOR3(1280 / 2, 720 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//固定枠
	rc = { 0,0,200,200 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(150, 255, 255, 255));
	//ノーツ
	KdMatrix scaleMat;
	notesMat = ringMat;
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	if (scale > 0.35f && scale < 0.7f) {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 0, 0));
	}
	else if (scale > 0.0f && scale < 0.35f) {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 0, 0));
	}
	else {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 255, 255));
	}

	//判定画像
	if (judgeFlg) {
		//judgeMat.CreateTrans();
		scaleMat.CreateScale(1.0f, 1.0f, 0);
		judgeMat = scaleMat * judgeMat;
		SPRITE->SetTransform(&judgeMat);
		rc = { 0,0,335,200 };
		if (resultTex)		SPRITE->Draw(resultTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		else SPRITE->Draw(judgeTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 255, 255));

	}


	SPRITE->End();

	//デバッグ文字
	char buf[100];
	rc = { 0,650,0,0 };
	sprintf_s(buf, sizeof(buf), "残りクリック回数：%d", clickNum);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGameScene::Draw3D()
{

}

void CGameScene::End()
{
	KdSafeRelease(ringTex);
	KdSafeRelease(notesTex);
	KdSafeRelease(judgeTex);
	KdSafeRelease(resultTex);
	KdSafeRelease(backTex);
	m_pSound->LDSB8->Stop();

}
