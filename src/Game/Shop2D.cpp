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
	Possession = DTWHOUCE.GetInt("Possession");
	//アイテムの値段
	RodPrice[0] = 1000;
	RodPrice[1] = 2500;
	RodPrice[2] = 4000;
	RodPrice[3] = 10000;
	RodPrice[4] = 20000;
	RodPrice[5] = 50000;
	RodPrice[6] = 100000;
	RodPrice[7] = 100000000;
	BaitPrice[0] = 100;
	BaitPrice[1] = 200;
	BaitPrice[2] = 500;
	BaitPrice[3] = 800;
	BaitPrice[4] = 1000;
	BaitPrice[5] = 3000;
	BaitPrice[6] = 5000;
	BaitPrice[7] = 50000000;
	ReelPrice[0] = 1000;
	ReelPrice[1] = 2000;
	ReelPrice[2] = 2500;
	ReelPrice[3] = 4000;
	ReelPrice[4] = 10000;
	ReelPrice[5] = 20000;
	ReelPrice[6] = 50000;
	ReelPrice[7] = 999999999;
	//リスト
	FrameTex = RESOURCE_MNG.GetTexture("Shop/ShopFrame.png");
	FrameMat.SetTrans(50.0f, 0.0f, 0.0f);

	ItemNameTextTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameText0.png");
	ItemNameTextMat.SetTrans( 50.0f, 0.0f, 0.0f);

	//アイテム説明枠
	ItemDesTex = RESOURCE_MNG.GetTexture("Shop/ItemDes.png");
	ItemDesMat.SetTrans(575.0f, 465.0f, 0.0f);
	//ステータス関係
	E_PowerTex = RESOURCE_MNG.GetTexture("Shop/E_power.png");
	E_PowerMat.SetTrans(850.0f, 435.0f, 0.0f);
	MoneyFrameTex = RESOURCE_MNG.GetTexture("Shop/MoneyFrame.png");
	MoneyFrameMat.SetTrans(840.0f, 10.0f, 0.0f);
	numberTex = RESOURCE_MNG.GetTexture("Shop/number.png");
	numberMat.SetTrans( 940.0f, 10.0f, 0.0f);
	statusTex = RESOURCE_MNG.GetTexture("Shop/statusC.png");
	statusMat.SetTrans(1280.0f / 2.0f, 640.0f / 2.0f, 0.0f);

	//エサ
	BaitTex = RESOURCE_MNG.GetTexture("Shop/Bait.png");
	BaitMat.SetTrans(735.0f, 125.0f, 0.0f);

	//タブ
	TabLeftTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab1.png");
	TabCenterTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab2.png");
	TabRightTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab3.png");
	TabLeftMat.  SetTrans(50.0f, 0.0f, 0.0f);
	TabCenterMat.SetTrans(50.0f, 0.0f, 0.0f);
	TabRightMat. SetTrans(50.0f, 0.0f, 0.0f);
	tabL = 0;
	tabC = 0;
	tabR = 0;

	//選択カーソル
	ListSelectTex = RESOURCE_MNG.GetTexture("Shop/ListSelect.png");
	ListSelectMat.SetTrans(50.0f, select[0], 0.0f);

	//購入不可ウィンドウ
	Can_tBuyTex = RESOURCE_MNG.GetTexture("Shop/Can'tBuy.png");
	Can_tBuyMat.SetTrans(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f);
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
		if (EnterDownFlg == false) {
			WindowPattern++; //0:非表示　1:ステータス  2:購入準備
			EnterFlg = true;
			EnterDownFlg = true;
		}
	}
	else {
		EnterDownFlg = false;
	}
	//バックスペースでウィンドウクローズ
	if (GetKey(VK_BACK) & 0x8000) {
		WindowPattern = 0;
		EnterFlg = false;
	}

	//購入処理
	if (WindowPattern == 2) {
		//足りないとき
		if ((Possession < RodPrice[cursor]) || (Possession < BaitPrice[cursor]) || (Possession < ReelPrice[cursor])) {
			Can_tBuyFlg = true;
		}
		//足りるとき
		else {
			if (tabPattern == 0)Possession -= RodPrice[cursor];
			if (tabPattern == 1)Possession -= BaitPrice[cursor];
			if (tabPattern == 2)Possession -= ReelPrice[cursor];
		}
		WindowPattern = 0;
		EnterFlg = false;
	}
	//
	if (Possession <= 0) {
		Possession = 0;
	}
	if (Can_tBuyFlg) {
		ctCnt++;
	}
	if (ctCnt >= 60) {
		Can_tBuyFlg = false;
		ctCnt = 0;
	}

	//=========================================
	// 表示
	//=========================================

	//選択カーソル
	for (int i = 0; i < LISTNUMBER; i++) {
		select[i] = i * 60.5f;
	}
	ListSelectMat.SetTrans(50.0f, select[cursor], 0.0f);
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
	TabLeftMat.SetTrans(50.0f, 0.0f - tabL, 0.0f);
	TabCenterMat.SetTrans(50.0f, 0.0f - tabC, 0.0f);
	TabRightMat.SetTrans(50.0f, 0.0f - tabR, 0.0f);


	//3つの能力値を合計し、３で割って/100する
	//0.0～1.0にする
	DTWHOUCE.SetNo("Quality", 1111);
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
	if (ReelTextFlg) {
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
	RECT rcStatus;
	if (EnterFlg == true) {
		if (tabPattern == 0) {

			rcStatus = { 500 * tabPattern,
						500 * cursor,
						500 * tabPattern + 500,
						500 * (cursor + 1)
			};

		}
		SPRITE->SetTransform(&statusMat);
		SPRITE->Draw(*statusTex, &rcStatus, &D3DXVECTOR3(250.0f, 250.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		//所持金
		RECT rcNum[] = {
		{  0    ,0, 50 * 1,50 },
		{ 50 * 1,0, 50 * 2,50 },
		{ 50 * 2,0, 50 * 3,50 },
		{ 50 * 3,0, 50 * 4,50 },
		{ 50 * 4,0, 50 * 5,50 },
		{ 50 * 5,0, 50 * 6,50 },
		{ 50 * 6,0, 50 * 7,50 },
		{ 50 * 7,0, 50 * 8,50 },
		{ 50 * 8,0, 50 * 9,50 },
		{ 50 * 9,0, 50 * 10,50 } };
		char cScore[64];
		sprintf_s(cScore, sizeof(cScore), "%d", Possession);
		numberMat.SetTrans(1210, 20, 0);
		int i;
		for (i = 0; cScore[i] != '\0'; i++);
		for (i -= 1; i >= 0; i--) {
			numberMat.MoveLocal({ -35,0,0 });
			SPRITE->SetTransform(&numberMat);
			SPRITE->Draw(*numberTex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		RECT rcCan_tBuy = { 0,0,600,100 };
		SPRITE->SetTransform(&Can_tBuyMat);
		if (Can_tBuyFlg) {
			SPRITE->Draw(*Can_tBuyTex, &rcCan_tBuy, &D3DXVECTOR3(300.0f, 50.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		SPRITE->End();
	}
}


void Shop2D::End()
{
	//所持金の再登録
	DTWHOUCE.SetInt("Possession", Possession);

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

}

int Shop2D::SetTabPattern()
{
	return tabPattern;
}

int Shop2D::SetCursor()
{
	return cursor;
}
