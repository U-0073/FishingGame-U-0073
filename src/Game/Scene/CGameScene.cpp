#include"../../System/KdLibrary/KdLibrary.h"
#include"../../System/FrameBase/CGameFrame.h"

#include "CGameScene.h"
#include"../GameProc.h"

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{
}

void CGameScene::Init()
{
	ringTex = RESOURCE_MNG.GetTexture("Ring5.png");
	notesTex = RESOURCE_MNG.GetTexture("ScaleRing2.png");
	backTex = RESOURCE_MNG.GetTexture("SeaBack002.png");

	ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
	SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
	notesMat = ringMat;
	backMat.CreateTrans(1280 / 2, 720 / 2, 0);
	//拡縮サイズ
	scale = 2.0f;
	speed = 0.02f;
	clickNum = 1;
	frame = 120;


	//曲選択
	MusicChoise = 3;// rand() % 5;
	switch (MusicChoise)
	{
	case 0:
		m_pSound = RESOURCE_MNG.GetSound("Phantom_Apartment_2");
		m_pSound->Playsound("Phantom_Apartment_2", true, true);
		break;
	case 1:
		m_pSound = RESOURCE_MNG.GetSound("Dance_Dance_Cats");
		m_pSound->Playsound("Dance_Dance_Cats", true, true);
		break;
	case 2:
		m_pSound = RESOURCE_MNG.GetSound("Green_Stage_2");
		m_pSound->Playsound("Green_Stage_2", true, true);
		break;
	case 3:
		m_pSound = RESOURCE_MNG.GetSound("Ride_On_The_Wind_2");
		m_pSound->Playsound("Ride_On_The_Wind_2", true, true);
		break;
	case 4:
		m_pSound = RESOURCE_MNG.GetSound("START!!");
		m_pSound->Playsound("START!!", true, true);
		break;
	}

	judgeFlg = 0;
	len = 10000;
	Check = true;
}

int CGameScene::Update()
{
	ShowCursor(true);
	GetCursorPos(&Mouse);
	ScreenToClient(GETHWND, &Mouse);

	frame--;

	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (!keyFlg) {
			//SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
			clickPos = { (float)Mouse.x,(float)Mouse.y,0.0f };
			KdVec3 ringPos = { ringMat._41, ringMat._42, ringMat._43 };
			len = ringMat.GetPos().LengthToTarget(clickPos);


			keyFlg = true;
			//clickNum--;
			//ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
			//notesMat = ringMat;
		}
		//judgeFlg = true;
	}
	else {
		keyFlg = false;
		//judgeFlg = false;
		//len = NULL;
		clickPos = { 0,0,0 };
	}


	//ノーツ判定処理
	//エクセレント（内側）の時の処理
	if (len <= 100 && scale > 0.75 && scale < 1.0) {//scale > 0.0 && scale < 0.35
		if (judgeFlg == 0) {
			judgeTex = RESOURCE_MNG.GetTexture("excellent1.png");
			judgeFlg = 1;//	成功
		}
	}
	//ミスの時の処理
	else {
		if (judgeFlg == 0) {
			if (scale < 0.7) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				judgeFlg = 2;//失敗
			}
			if (keyFlg == true && scale > 1.0) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				judgeFlg = 2;//失敗

			}
			if (keyFlg == true && len > 100 && scale > 0.75 && scale < 1.0) {//scale > 0.0 && scale < 0.35
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				judgeFlg = 2;//失敗

			}
		}
	}


	//scale縮小
	if (Check) {
		scale -= speed;
		if (scale < 0.0f) {
			len = 10000;
			clickPos = { 0,0,0 };
			clickNum--;
			//デバッグ用回避手段
			if (clickNum <= 0) {
				Check = false;

				//曲変更
				m_pSound->LDSB8->Stop();
				m_pSound = RESOURCE_MNG.GetSound("レベルが上がったり何かをクリアした時の短いジングル");
				m_pSound->Playsound("レベルが上がったり何かをクリアした時の短いジングル", true, false);

				FADE.Start(6.5);
				return TITLE;
			}

			judgeFlg = 0;
			ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
			SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
			notesMat = ringMat;

			scale = 2.0f;
		}
	}


	return GAME;
}

void CGameScene::Draw2D()
{
	//背景
	RECT rc = { 0,0,1280,720 };
	SPRITE->SetTransform(&backMat);
	SPRITE->Draw(*backTex, &rc, &D3DXVECTOR3(1280 / 2, 720 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//固定枠
	rc = { 0,0,200,200 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(*ringTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(150, 255, 255, 255));
	//ノーツ
	KdMatrix scaleMat;
	notesMat = ringMat;
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	if (scale > 0.7f && scale < 1.0f) {
		SPRITE->Draw(*notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else {
		SPRITE->Draw(*notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//判定画像
	if (judgeFlg != 0) {
		//judgeMat.CreateTrans();
		scaleMat.CreateScale(1.0f, 1.0f, 0);
		judgeMat = scaleMat * judgeMat;
		SPRITE->SetTransform(&judgeMat);
		rc = { 0,0,335,200 };
		if (resultTex)		SPRITE->Draw(*resultTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		else SPRITE->Draw(*judgeTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 255, 255));

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
	backTex = nullptr;
	ringTex = nullptr;
	notesTex = nullptr;
	judgeTex = nullptr;
	resultTex = nullptr;
	m_pSound->LDSB8->Stop();
	m_pSound = nullptr;
}
