#include"../System/KdLibrary/KdLibrary.h"
#include"Shop2D.h"

void SafeReleaseTex(LPDIRECT3DTEXTURE9 tex) {
	if (tex != nullptr) tex->Release();
}



Shop2D::Shop2D()
{
}

Shop2D::~Shop2D()
{
}

void Shop2D::Init()
{
	//所持金の確認
	Possession = (int)DTWHOUCE.GetNo("Possession");

	//リスト
	FrameTex = RESOURCE_MNG.GetTexture("Shop/ShopFrame.png");
	D3DXMatrixTranslation(&FrameMat, 50.0f, 0.0f, 0.0f);

	ItemNameTextTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameText0.png");
	D3DXMatrixTranslation(&ItemNameTextMat, 50.0f, 0.0f, 0.0f);

	//アイテム説明枠
	ItemDesTex = RESOURCE_MNG.GetTexture("Shop/ItemDes.png");
	D3DXMatrixTranslation(&ItemDesMat, 575.0f, 465.0f, 0.0f);
	//ステータス関係
	E_PowerTex = RESOURCE_MNG.GetTexture("Shop/E_power.png");
	D3DXMatrixTranslation(&E_PowerMat, 850.0f, 435.0f, 0.0f);
	MoneyFrameTex = RESOURCE_MNG.GetTexture("Shop/MoneyFrame.png");
	D3DXMatrixTranslation(&MoneyFrameMat, 840.0f, 10.0f, 0.0f);
	numberTex = RESOURCE_MNG.GetTexture("Shop/number.png");
	D3DXMatrixTranslation(&numberMat, 940.0f, 10.0f, 0.0f);
	statusTex = RESOURCE_MNG.GetTexture("Shop/statusC.png");
	D3DXMatrixTranslation(&statusMat, 1280.0f / 2.0f, 640.0f / 2.0f, 0.0f);

	//エサ
	BaitTex = RESOURCE_MNG.GetTexture("Shop/Bait.png");
	D3DXMatrixTranslation(&BaitMat, 735.0f, 125.0f, 0.0f);

	//タブ
	TabLeftTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab1.png");
	TabCenterTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab2.png");
	TabRightTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab3.png");
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f, 0.0f);
	tabL = 0;
	tabC = 0;
	tabR = 0;

	//選択カーソル
	ListSelectTex = RESOURCE_MNG.GetTexture("Shop/ListSelect.png");
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[0], 0.0f);
}

void Shop2D::Update()
{
	//=========================================
	// 操作
	//=========================================

	//上下キーでカーソル移動
	if (GetKey(VK_DOWN) & 0x8000) {
		if (KeyDownFlg == false) {
			cursor++;
			if (cursor >= LISTNUMBER - 1)cursor = LISTNUMBER - 1;
			KeyDownFlg = true;
		}
	}
	else {
		KeyDownFlg = false;
	}

	if (GetKey(VK_UP) & 0x8000) {
		if (KeyUpFlg == false) {
			cursor--;
			if (cursor <= 0)cursor = 0;
			KeyUpFlg = true;
		}
	}
	else {
		KeyUpFlg = false;
	}

	//左右キーでタブ移動
	if (GetKey(VK_LEFT) & 0x8000) {
		if (KeyLeftFlg == false) {

			tabPattern--;
			if (tabPattern <= 0)tabPattern = 0;
			KeyLeftFlg = true;
		}
	}
	else {
		KeyLeftFlg = false;
	}

	if (GetKey(VK_RIGHT) & 0x8000) {
		if (KeyRightFlg == false) {

			tabPattern++;
			if (tabPattern >= 2)tabPattern = 2;
			KeyRightFlg = true;
		}
	}
	else {
		KeyRightFlg = false;
	}

	//エンターキーでウィンドウオープン
	if (GetKey(VK_RETURN) & 0x8000) {
		enterFlg = true;
	}
	//バックスペースでウィンドウクローズ
	if (GetKey(VK_BACK) & 0x8000) {
		enterFlg = false;
	}

	//=========================================
	// 表示
	//=========================================

	//選択カーソル
	for (int i = 0; i < LISTNUMBER; i++) {
		select[i] = i * 60.5f;
	}
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[cursor], 0.0f);
	//タブ
	if (tabPattern == 0) {
		tabL = 43; tabC = 0; tabR = 0;
		RodTextFlg = true;
		BaitTextFlg = false;
		ReelTextFlg = false;
	}
	if (tabPattern == 1) {
		tabL = 0; tabC = 43; tabR = 0;
		RodTextFlg = false;
		BaitTextFlg = true;
		ReelTextFlg = false;
	}
	if (tabPattern == 2) {
		tabL = 0; tabC = 0; tabR = 43;
		RodTextFlg = false;
		BaitTextFlg = false;
		ReelTextFlg = true;
	}
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f - tabL, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f - tabC, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f - tabR, 0.0f);

	//能力及び購入ウィンドウ

}

void Shop2D::Draw2D()
{
	
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//タグ
	RECT rcTagL = { 0,0,500,720 };
	SPRITE->SetTransform(&TabLeftMat);
	SPRITE->Draw(*TabLeftTex, &rcTagL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagC = { 0,0,500,720 };
	SPRITE->SetTransform(&TabCenterMat);
	SPRITE->Draw(*TabCenterTex, &rcTagC, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagR = { 0,0,500,720 };
	SPRITE->SetTransform(&TabRightMat);
	SPRITE->Draw(*TabRightTex, &rcTagR, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	//リスト
	RECT rcFrame = { 0,0,500,720 };
	SPRITE->SetTransform(&FrameMat);
	SPRITE->Draw(*FrameTex, &rcFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//選択カーソル
	RECT rcSelect = { 0,0,500,720 };
	SPRITE->SetTransform(&ListSelectMat);
	SPRITE->Draw(*ListSelectTex, &rcSelect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//アイテム説明
	RECT rcItemDes;
	//リスト文字
	RECT rcItemNameText;
	if (RodTextFlg) {
		rcItemNameText = { 0,0,500,720 };
		//カーソル位置に応じてアイテム説明変更
		switch (cursor)
		{
		case 0:
			rcItemDes = { 0,0,650,200 };
			break;
		case 1:
			rcItemDes = { 0,200,650,400 };
			break;
		case 2:
			rcItemDes = { 0,400,650,600 };
			break;
		case 3:
			rcItemDes = { 0,600,650,800 };
			break;
		case 4:
			rcItemDes = { 0,800,650,1000 };
			break;
		case 5:
			rcItemDes = { 0,1000,650,1200 };
			break;
		case 6:
			rcItemDes = { 0,1200,650,1400 };
			break;
		case 7:
			rcItemDes = { 0,1400,650,1600 };
			break;
		}
	}
	if (BaitTextFlg) {
		rcItemNameText = { 500,0,1000,720 };
		//カーソル位置に応じてアイテム説明変更
		switch (cursor)
		{
		case 0:
			rcItemDes = { 650,0,1300,200 };
			break;
		case 1:
			rcItemDes = { 650,200,1300,400 };
			break;
		case 2:
			rcItemDes = { 650,400,1300,600 };
			break;
		case 3:
			rcItemDes = { 650,600,1300,800 };
			break;
		case 4:
			rcItemDes = { 650,800,1300,1000 };
			break;
		case 5:
			rcItemDes = { 650,1000,1300,1200 };
			break;
		case 6:
			rcItemDes = { 650,1200,1300,1400 };
			break;
		case 7:
			rcItemDes = { 650,1400,1300,1600 };
			break;
		}
	}
	if (ReelTextFlg){
		rcItemNameText = { 1000,0,1500,720 };
		//カーソル位置に応じてアイテム説明変更
		switch (cursor)
		{
		case 0:
			rcItemDes = { 1300,0,1950,200 };
			break;
		case 1:
			rcItemDes = { 1300,200,1950,400 };
			break;
		case 2:
			rcItemDes = { 1300,400,1950,600 };
			break;
		case 3:
			rcItemDes = { 1300,600,1950,800 };
			break;
		case 4:
			rcItemDes = { 1300,800,1950,1000 };
			break;
		case 5:
			rcItemDes = { 1300,1000,1950,1200 };
			break;
		case 6:
			rcItemDes = { 1300,1200,1950,1400 };
			break;
		case 7:
			rcItemDes = { 1300,1400,1950,1600 };
			break;
		}
	}
	SPRITE->SetTransform(&ItemNameTextMat);
	SPRITE->Draw(*ItemNameTextTex, &rcItemNameText, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	SPRITE->SetTransform(&ItemDesMat);
	SPRITE->Draw(*ItemDesTex, &rcItemDes, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcE_Power = { 0,0,350,39 };
	SPRITE->SetTransform(&E_PowerMat);
	SPRITE->Draw(*E_PowerTex, &rcE_Power, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcMoneyFrame = { 0,0,400,70 };
	SPRITE->SetTransform(&MoneyFrameMat);
	SPRITE->Draw(*MoneyFrameTex, &rcMoneyFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//エサ
	RECT rcBait;
	if (BaitTextFlg) {
		switch (cursor)
		{
		case 0:
			rcBait = { 0,0,300,328 };
			break;
		case 1:
			rcBait = { 300,0,600,328 };
			break;
		case 2:
			rcBait = { 600,0,900,328 };
			break;
		case 3:
			rcBait = { 900,0,1200,328 };
			break;
		case 4:
			rcBait = { 1200,0,1500,328 };
			break;
		case 5:
			rcBait = { 1500,0,1800,328 };
			break;
		case 6:
			rcBait = { 1800,0,2100,328 };
			break;
		case 7:
			rcBait = { 2100,0,2400,328 };
			break;
		}
		SPRITE->SetTransform(&BaitMat);
		SPRITE->Draw(*BaitTex, &rcBait, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//ステータスウィンドウ
	//釣り竿
	RECT rcStatus;;
	if (enterFlg == true) {
		if (tabPattern == 0) {
			switch (cursor)
			{
			case 0:
				rcStatus = { 0,0,500,500 };
				break;
			case 1:
				rcStatus = { 0,500 * 1,500,500 * 2};
				break;
			case 2:
				rcStatus = { 0,500 * 2,500,500 * 3};
				break;
			case 3:
				rcStatus = { 0,500 * 3,500,500 * 4};
				break;
			case 4:
				rcStatus = { 0,500 * 4,500,500 * 5};
				break;
			case 5:
				rcStatus = { 0,500 * 5,500,500 * 6};
				break;
			case 6:
				rcStatus = { 0,500 * 6,500,500 * 7};
				break;
			case 7:
				rcStatus = { 0,500 * 7,500,500 * 8};
				break;
			}
		}
		//餌
		if (tabPattern == 1) {
			switch (cursor)
			{
			case 0:
				rcStatus = { 500,0,1000,500 };
				break;
			case 1:
				rcStatus = { 500,500 * 1,1000,500 * 2 };
				break;
			case 2:
				rcStatus = { 500,500 * 2,1000,500 * 3 };
				break;
			case 3:
				rcStatus = { 500,500 * 3,1000,500 * 4 };
				break;
			case 4:
				rcStatus = { 500,500 * 4,1000,500 * 5 };
				break;
			case 5:
				rcStatus = { 500,500 * 5,1000,500 * 6 };
				break;
			case 6:
				rcStatus = { 500,500 * 6,1000,500 * 7 };
				break;
			case 7:
				rcStatus = { 500,500 * 7,1000,500 * 8 };
				break;
			}
		}
		//リール
		if (tabPattern == 2) {
			switch (cursor)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			}
		}
	}
	SPRITE->SetTransform(&statusMat);
	SPRITE->Draw(*statusTex, &rcStatus, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//所持金
	RECT rcNum[] = {
	{  0    ,0, 50 *  1,50 },
	{ 50 * 1,0, 50 *  2,50 },
	{ 50 * 2,0, 50 *  3,50 },
	{ 50 * 3,0, 50 *  4,50 },
	{ 50 * 4,0, 50 *  5,50 },
	{ 50 * 5,0, 50 *  6,50 },
	{ 50 * 6,0, 50 *  7,50 },
	{ 50 * 7,0, 50 *  8,50 },
	{ 50 * 8,0, 50 *  9,50 },
	{ 50 * 9,0, 50 * 10,50 } };
	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", Possession);
	D3DXMatrixTranslation(&numberMat, 1210, 20, 0);
	D3DXMatrixTranslation(&transMat, -35, 0, 0);
	int i;
	for (i = 0; cScore[i] != '\0'; i++);
	for (i -= 1; i >= 0; i--) {
		numberMat *= transMat;
		SPRITE->SetTransform(&numberMat);
		SPRITE->Draw(*numberTex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SPRITE->End();
}

void Shop2D::Draw3D()
{
}

void Shop2D::End()
{
	m_pModel = nullptr;
	FrameTex = nullptr;
	FrameSecTex = nullptr;
	FrameSrdTex = nullptr;
	ItemNameTextTex = nullptr;
	ItemDesTex = nullptr;
	TabLeftTex = nullptr;
	TabCenterTex = nullptr;
	TabRightTex = nullptr;
	ListSelectTex = nullptr;
	BaitTex = nullptr;

	//所持金の再登録
	DTWHOUCE.SetNo("Possession", Possession);
}

int Shop2D::SetTabPattern()
{
	return tabPattern;
}

int Shop2D::SetCursor()
{
	return cursor;
}
