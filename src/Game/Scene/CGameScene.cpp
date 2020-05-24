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

	//拡縮サイズ
	scale = 2.0f;
	speed = 0.0215f;
	clickNum = 10;
	clickCNT = clickNum;
	frame = 240;



	judgeFlg = 0;
	len = 10000;


	//初期の曲
	m_pSound = RESOURCE_MNG.GetSound("スタート時のカウントダウン音");
	m_pSound->Playsound("スタート時のカウントダウン音", true, false);


	//譜面描画制御用フラグ
	Check = false;
	frameStopper = false;

	//score
	Excellent = 0;
	Miss = 0;

	MusicChoise = rand() % 6;

}

int CGameScene::Update()
{
	ShowCursor(true);
	GetCursorPos(&Mouse);
	ScreenToClient(GETHWND, &Mouse);


	if (!frameStopper) {
		frame--;
		if (frame < 0) {
			frame = 0;

			m_pSound->LDSB8->Stop();
			std::string name;
			//曲選択
			switch (MusicChoise)
			{
			case 0:
				name = "CGSSound/Phantom_Apartment_2";
				break;
			case 1:
				name = "CGSSound/Dance_Dance_Cats";
				break;
			case 2:
				name = "CGSSound/Green_Stage_2";
				break;
			case 3:
				name = "CGSSound/Ride_On_The_Wind_2";
				break;
			case 4:
				name = "CGSSound/START!!";
				break;
			case 5:
				name = "CGSSound/Ride_On_The_Wind";
				break;
			}
			m_pSound = RESOURCE_MNG.GetSound(name);
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


	//ノーツ判定処理
	//エクセレント（内側）の時の処理
	if (len <= 100 && scale > 0.75 && scale < 1.0) {
		if (judgeFlg == 0) {
			judgeTex = RESOURCE_MNG.GetTexture("excellent1.png");
			Excellent++;
			judgeFlg = 1;//	成功
		}
	}
	//ミスの時の処理
	else {
		if (judgeFlg == 0) {
			if (scale < 0.7) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = 2;//失敗
			}
			if (keyFlg == true && scale > 1.0) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = 2;//失敗

			}
			if (keyFlg == true && len > 100 && scale > 0.75 && scale < 1.0) {
				judgeTex = RESOURCE_MNG.GetTexture("miss.png");
				Miss++;
				judgeFlg = 2;//失敗

			}
		}
	}


	if (Check) {

		//scale縮小
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

				//ゲーム結果をDTWHOUCEに保存する
				int calcAve = Excellent / (Excellent + Miss);//calcAveは全ノーツのエクセレント率
				bool clear;
				if (calcAve >= 0.6) { clear = true; }
				if (calcAve < 0.6) { clear = false; }
				score.Set(Excellent, Miss, clear);
				DTWHOUCE.SetVec("score", score);
				//保存後、リザルトシーンヘ
				FADE.Start(6.5);
				return RESULT;
			}

			judgeFlg = 0;
			ringMat.SetTrans((rand() % 1080) + 100, (rand() % 520) + 100, 0);
			SetPos(KdVec3(ringMat._41, ringMat._42, ringMat._43));
			notesMat = ringMat;


			clickCNT--;
			if (clickNum == 0)clickCNT = 0;


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
	scaleMat.SetScale(scale, scale, 0);
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
		//scaleMat.CreateScale(1.0f, 1.0f, 0);
		//judgeMat = scaleMat * judgeMat;
		SPRITE->SetTransform(&judgeMat);
		rc = { 0,0,335,200 };
		if (resultTex)		SPRITE->Draw(*resultTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		else SPRITE->Draw(*judgeTex, &rc, &D3DXVECTOR3(335 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(125, 255, 255, 255));

	}


	SPRITE->End();

	//デバッグ文字
	char buf[100];
	rc = { 0,650,0,0 };
	sprintf_s(buf, sizeof(buf), "残り譜面数：%d", clickCNT);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	char Excel[20];
	rc = { 0,600,0,0 };
	sprintf_s(Excel, sizeof(Excel), "Excellent：%d", Excellent);
	FONT->DrawText(NULL, Excel, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	char Ms[20];
	rc = { 0,625,0,0 };
	sprintf_s(Ms, sizeof(Ms), "Miss：%d", Miss);
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
