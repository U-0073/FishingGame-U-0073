#include"../System/KdLibrary/KdLibrary.h"
#include "../System/FrameBase/CGameFrame.h"

#include "CGameScene.h"
#include"GameProc.h"

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{
}

void CGameScene::Init()
{
	ringTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Ring5.png");
	notesTex = *RESOURCE_MNG.GetTexture("Resource/Texture/ScaleRing2.png");
	backTex = *RESOURCE_MNG.GetTexture("Resource/Texture/SeaBack002.png");

	ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
	notesMat = ringMat;
	backMat.CreateTrans(1280 / 2, 720 / 2, 0);
	//�g�k�T�C�Y
	scale = 2.0f;
	speed = 0.01f;
	clickNum = 10;
	frame = 120;

	m_pSound = RESOURCE_MNG.GetSound("Resource/Sound/Phantom_Apartment_2.wav");
	m_pSound->Playsound("Resource/Sound/Phantom_Apartment_2.wav", true, true);

}

int CGameScene::Update()
{
	GetCursorPos(&Mouse);
	ScreenToClient(GETHWND, &Mouse);

	frame--;

	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (!keyFlg) {
			SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
			clickPos = { (float)Mouse.x,(float)Mouse.y,0.0f };
			KdVec3 ringPos = { ringMat._41, ringMat._42, ringMat._43 };
			len = ringMat.GetPos().LengthToTarget(clickPos);


			keyFlg = true;
			clickNum--;
			scale = 2.0f;
			ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
			notesMat = ringMat;


		}
		judgeFlg = true;
	}
	else if (scale < 0.0f) {
		judgeFlg = true;
		judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/miss.png");
		clickNum--;
		ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
		scale = 2.0f;
	}
	else {
		keyFlg = false;
		judgeFlg = false;
		len = NULL;
		clickPos = { 0,0,0 };
	}


	//�m�[�c���菈��
	//�O���[�g�i�O���j�̎��̏���
	if (len < 100 && len >= 50) {//scale > 0.35 && scale < 0.7
		judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/great.png");
	}
	//�G�N�Z�����g�i�����j�̎��̏���
	else if (len < 50) {//scale > 0.0 && scale < 0.35
		judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/excellent1.png");
	}
	//�~�X�̎��̏���
	else {
		judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/miss.png");
	}


	//scale�k��
	scale -= speed;
	/*if (scale < 0.0f) {
		judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/miss.png");
		clickNum--;
		ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
		scale = 2.0f;
	}*/

	//�f�o�b�O�p�����i
	if (clickNum <= 0) {
		FADE.Start(5);
		return TITLE;
	}

	return GAME;
}

void CGameScene::Draw2D()
{
	//�w�i
	RECT rc = { 0,0,1280,720 };
	SPRITE->SetTransform(&backMat);
	SPRITE->Draw(backTex, &rc, &D3DXVECTOR3(1280 / 2, 720 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//�Œ�g
	rc = { 0,0,200,200 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(ringTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(150, 255, 255, 255));
	//�m�[�c
	KdMatrix scaleMat;
	notesMat = ringMat;
	scaleMat.CreateScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	if (scale > 0.7f && scale < 1.0f) {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//����摜
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

	//�f�o�b�O����
	char buf[100];
	rc = { 0,650,0,0 };
	sprintf_s(buf, sizeof(buf), "�c��N���b�N�񐔁F%d", clickNum);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGameScene::Draw3D()
{

}

void CGameScene::End()
{
	if (ringTex != nullptr)ringTex->Release();
	if (notesTex != nullptr)notesTex->Release();
	if (backTex != nullptr) backTex->Release();

	KdSafeRelease(ringTex);
	KdSafeRelease(notesTex);
	KdSafeRelease(judgeTex);
	KdSafeRelease(resultTex);
	KdSafeRelease(backTex);
	m_pSound->LDSB8->Stop();

}
