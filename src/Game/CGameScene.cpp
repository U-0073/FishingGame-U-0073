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
	//�g�k�T�C�Y
	scale = 2.0f;
	//Lv1�`5
	//level = rand() % 6 + 1;
	level = 5;
	dist = level;
	speed = 0.005f;
	clickNum = 10;
	frame = wait = 120;

	m_pSound = RESOURCE_MNG.GetSound("Resource/Sound/wave3.wav");
	m_pSound->Playsound("Resource/Sound/wave3.wav", true, true);

}

int CGameScene::Update()
{
	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (!keyFlg) {
			//����\�����̓N���b�N�ł��Ȃ�
			if (frame == wait) {
				//�O���[�g�i�O���j�̎��̏���
				if (scale > 0.35 && scale < 0.7) {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/great.png");
					dist -= 1.0f;
					//speed += 0.002;
				}
				//�G�N�Z�����g�i�����j�̎��̏���
				else if (scale > 0.0 && scale < 0.35) {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/excellent1.png");
					dist -= 0.5f;
					//speed += 0.002 * level;
				}
				//�~�X�̎��̏���
				else {
					judgeTex = *RESOURCE_MNG.GetTexture("Resource/Texture/miss.png");
				}
				keyFlg = true;
				clickNum--;
				frame--;
				scale = 2.0f;
				ringMat.CreateTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
				notesMat = ringMat;

			}
		}
	}
	else { keyFlg = false; }


	scale -= speed;
	if (scale < 0.0f) {
		scale = 2.0f;
	}
	//frame�������Ă��珈���p��
	if (frame < wait)
	{
		frame--;
		//�`��I����
		if (frame < 0) {
			frame = wait;
			//�ނ�؂��Ă�����
			if (dist <= 0)
			{
				if (resultTex) {
					FADE.Start(5);
					return MAP;
				}
				//�ނꂽ�̉摜��\��
				resultTex = *RESOURCE_MNG.GetTexture("Resource/Texture/clear.png");
				frame--;
			}
			//�ނ�؂�Ȃ�������
			else if (clickNum <= 0) {
				if (resultTex) {
					FADE.Start(5);
					return MAP;
				}
				resultTex = *RESOURCE_MNG.GetTexture("Resource/Texture/escape.png");
				frame--;
			}

		}
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
	else if (scale > 0.0f && scale < 0.35f) {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else {
		SPRITE->Draw(notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//����摜
	if (frame < wait) {
		judgeMat.CreateTrans(KdVec3(1280 / 2, 720 / 2, 0));
		scaleMat.CreateScale(2.0f, 2.0f, 0);
		judgeMat = scaleMat * judgeMat;
		SPRITE->SetTransform(&judgeMat);
		rc = { 0,0,335,200 };
		if (resultTex)		SPRITE->Draw(resultTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		else SPRITE->Draw(judgeTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}




	SPRITE->End();

	//�f�o�b�O����
	rc = { 0,0,0,0 };
	char buf[100];
	sprintf_s(buf, sizeof(buf), "scale:%4.5f dist:%4.1f", scale, dist);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

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
	KdSafeRelease(ringTex);
	KdSafeRelease(notesTex);
	KdSafeRelease(judgeTex);
	KdSafeRelease(resultTex);
	KdSafeRelease(backTex);
}
