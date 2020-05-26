#include"../../System/KdLibrary/KdLibrary.h"
#include"../../System/FrameBase/CGameFrame.h"

#include "CGameScene.h"

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{
}

void CGameScene::Init()
{
	srand(timeGetTime());

	ringTex = RESOURCE_MNG.GetTexture("Ring5.png");
	notesTex = RESOURCE_MNG.GetTexture("ScaleRing2.png");
	backTex = RESOURCE_MNG.GetTexture("SeaBack002.png");

	ringMat.SetTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
	SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
	notesMat = ringMat;
	backMat.SetTrans(1280 / 2, 720 / 2, 0);

	//�g�k�T�C�Y
	scale = scaleInitialize;
	speed = EFReduction;
	clickNum = clickInitialize;
	clickCNT = clickInitialize;
	frame = MFInitialize;



	judgeFlg = Default_judge;
	len = defLenInitialize;


	//�����̋�
	m_pSound = RESOURCE_MNG.GetSound("�X�^�[�g���̃J�E���g�_�E����");
	m_pSound->Playsound("�X�^�[�g���̃J�E���g�_�E����", true, false);
	m_pSound->SetVol(0.9);


	//���ʕ`�搧��p�t���O
	Check = false;
	frameStopper = false;

	//score
	Excellent = ZEROreturn;
	Miss = ZEROreturn;

	MusicChoise = rand() % MusicGenerally;

}

int CGameScene::Update()
{
	ShowCursor(true);
	GetCursorPos(&Mouse);
	ScreenToClient(GETHWND, &Mouse);


	if (!frameStopper) {
		frame--;
		if (frame < ZEROreturn) {
			frame = ZEROreturn;

			m_pSound->LDSB8->Stop();
			std::string name;
			//�ȑI��
			switch (MusicChoise)
			{
			case PhantomA2:
				name = "CGSSound/Phantom_Apartment_2";
				break;
			case DDCats:
				name = "CGSSound/Dance_Dance_Cats";
				break;
			case GStage2:
				name = "CGSSound/Green_Stage_2";
				break;
			case ROTWind2:
				name = "CGSSound/Ride_On_The_Wind_2";
				break;
			case START:
				name = "CGSSound/START!!";
				break;
			case ROTWindSP:
				name = "CGSSound/Ride_On_The_Wind";
				break;
			}
			m_pSound = RESOURCE_MNG.GetSound(name);
			m_pSound->SetVol(0.9);
			m_pSound->Playsound(name, true, true);


			clickCNT--;
			Check = true;
			frameStopper = true;
		}
	}


	if (GetKey(VK_LBUTTON) & 0x8000) {
		if (!keyFlg) {
			clickPos = { (float)Mouse.x,(float)Mouse.y,0.0f };
			KdVec3 ringPos = { ringMat._41, ringMat._42, ringMat._43 };
			len = ringMat.GetPos().LengthToTarget(clickPos);


			keyFlg = true;
		}
	}
	else {
		keyFlg = false;
		clickPos = { 0,0,0 };
	}


	//�m�[�c���菈��
	//�G�N�Z�����g�i�����j�̎��̏���
	if (len <= Length && scale > judgeMin && scale < judgeMax) {
		if (judgeFlg == Default_judge) {
			judgeTex = RESOURCE_MNG.GetTexture("excellent1.png");
			Excellent++;
			judgeFlg = Excellent_judge;//	����
		}
	}
	//�~�X�̎��̏���
	else {
		if (judgeFlg == Default_judge) {
			if (scale < judgeMin) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = Miss_judge;//���s
			}
			if (keyFlg == true && scale > judgeMax) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = Miss_judge;//���s

			}
			if (keyFlg == true && len > Length && scale > judgeMin && scale < judgeMax) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = Miss_judge;//���s

			}
		}
	}


	if (Check) {

		//scale�k��
		scale -= speed;
		if (scale < scaleLimit) {
			len = defLenInitialize;
			clickPos = { 0,0,0 };
			clickNum--;
			//�f�o�b�O�p�����i
			if (clickNum <= ZEROreturn) {
				Check = false;

				//�ȕύX
				m_pSound->LDSB8->Stop();
				m_pSound = RESOURCE_MNG.GetSound("���x�����オ�����艽�����N���A�������̒Z���W���O��");
				m_pSound->Playsound("���x�����オ�����艽�����N���A�������̒Z���W���O��", true, false);

				//�Q�[�����ʂ�DTWHOUCE�ɕۑ�����
				bool clear;

				if (Excellent + Miss != 0) {
					float calcAve = (float)Excellent / (Excellent + Miss);//calcAve�͑S�m�[�c�̃G�N�Z�����g��
					if (calcAve >= FishSuccess) { clear = true; }
					if (calcAve < FishSuccess) { clear = false; }
				}
				else {
					clear = false;
				}
				score.Set(Excellent, Miss, clear);
				DTWHOUCE.SetVec("score", score);
				//�ۑ���A���U���g�V�[���w
				FADE.Start(6.5);
				return RESULT;
			}

			judgeFlg = Default_judge;
			ringMat.SetTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
			SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
			notesMat = ringMat;


			clickCNT--;
			if (clickNum == ZEROreturn)clickCNT = ZEROreturn;
			scale = scaleInitialize;
		}
	}

	return GAME;
}

void CGameScene::Draw2D()
{
	//�w�i
	RECT rc = { 0,0,1280,720 };
	SPRITE->SetTransform(&backMat);
	SPRITE->Draw(*backTex, &rc, &D3DXVECTOR3(1280 / 2, 720 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//�Œ�g
	rc = { 0,0,200,200 };
	SPRITE->SetTransform(&ringMat);
	SPRITE->Draw(*ringTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(150, 255, 255, 255));
	//�m�[�c
	KdMatrix scaleMat;
	notesMat = ringMat;
	scaleMat.SetScale(scale, scale, 0);
	notesMat = scaleMat * notesMat;
	SPRITE->SetTransform(&notesMat);
	if (scale > judgeMin && scale < judgeMax) {
		SPRITE->Draw(*notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else {
		SPRITE->Draw(*notesTex, &rc, &D3DXVECTOR3(100, 100, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//����摜
	if (judgeFlg != Default_judge) {
		SPRITE->SetTransform(&judgeMat);
		rc = { 0,0,335,200 };
		if (resultTex)		SPRITE->Draw(*resultTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		else SPRITE->Draw(*judgeTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 255, 255));
	}


	SPRITE->End();

	//�f�o�b�O����
	char buf[100];
	rc = { 0,650,0,0 };
	sprintf_s(buf, sizeof(buf), "�c�蕈�ʐ��F%d", clickCNT);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	char Excel[20];
	rc = { 0,600,0,0 };
	sprintf_s(Excel, sizeof(Excel), "Excellent�F%d", Excellent);
	FONT->DrawText(NULL, Excel, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	char Ms[20];
	rc = { 0,625,0,0 };
	sprintf_s(Ms, sizeof(Ms), "Miss�F%d", Miss);
	FONT->DrawText(NULL, Ms, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));



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
