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
	ItemNameTextMat.SetTrans(50.0f, 0.0f, 0.0f);

	//アイテム説明枠
	ItemDesTex = RESOURCE_MNG.GetTexture("Shop/ItemDes.png");
	ItemDesMat.SetTrans(575.0f, 465.0f, 0.0f);
	//ステータス関係
	E_PowerTex = RESOURCE_MNG.GetTexture("Shop/E_power.png");
	E_PowerMat.SetTrans(850.0f, 435.0f, 0.0f);
	MoneyFrameTex = RESOURCE_MNG.GetTexture("Shop/MoneyFrame.png");
	MoneyFrameMat.SetTrans(840.0f, 10.0f, 0.0f);
	numberTex = RESOURCE_MNG.GetTexture("Shop/number.png");
	numberMat.SetTrans(940.0f, 10.0f, 0.0f);
	statusTex = RESOURCE_MNG.GetTexture("Shop/statusC.png");
	statusMat.SetTrans(1280.0f / 2.0f, 640.0f / 2.0f, 0.0f);

	//エサ
	BaitTex = RESOURCE_MNG.GetTexture("Shop/Bait.png");
	BaitMat.SetTrans(735.0f, 125.0f, 0.0f);

	//タブ
	TabLeftTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab1.png");
	TabCenterTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab2.png");
	TabRightTex = RESOURCE_MNG.GetTexture("Shop/ShopFrameTab3.png");
	TabLeftMat.SetTrans(50.0f, 0.0f, 0.0f);
	TabCenterMat.SetTrans(50.0f, 0.0f, 0.0f);
	TabRightMat.SetTrans(50.0f, 0.0f, 0.0f);
	tabL = 0;
	tabC = 0;
	tabR = 0;

	//選択カーソル
	ListSelectTex = RESOURCE_MNG.GetTexture("Shop/ListSelect.png");
	ListSelectMat.SetTrans(50.0f, select[0], 0.0f);

	//購入不可ウィンドウ
	Can_tBuyTex = RESOURCE_MNG.GetTexture("Shop/Can'tBuy.png");
	Can_tBuyMat.SetTrans(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f);


	BuyItem.x = -1;
	BuyItem.y = -1;
	BuyItem.z = -1;
	OpenItem.x = 0;
	OpenItem.y = 0;
	OpenItem.z = 0;
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
		//開放してたら
		if (BuyItem.x < OpenItem.x) {
			OpenItem.x++;
		}

		//所持金が足りないとき
		if ((Possession < RodPrice[cursor]) || (Possession < BaitPrice[cursor]) || (Possession < ReelPrice[cursor])) {
			Can_tBuyFlg = true;
		}
		//足りるとき
		else {
			if (tabPattern == 0) {
				Possession -= RodPrice[cursor];
				BuyItem.x++;
			}
			if (tabPattern == 1) {
				Possession -= BaitPrice[cursor];
				BuyItem.y++;
			}
			if (tabPattern == 2) {
				Possession -= ReelPrice[cursor];
				BuyItem.z++;
			}
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
		if (ctCnt >= 60) {
			Can_tBuyFlg = false;
			ctCnt = 0;
		}
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
	//0.0〜1.0にする
	DTWHOUCE.SetNo("Quality", 1111);

	//今、釣り竿、エサ、リールを上から何番目まで買ったかを保存する
	//DTWHOUCE.SetVec("BuyPattern", );
}

void Shop2D::Draw2D()
{

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//タグ
	RECT rcTag = { 0,0,500,720 };
	SPRITE->SetTransform(&TabLeftMat);
	SPRITE->Draw(*TabLeftTex, &rcTag, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->SetTransform(&TabCenterMat);
	SPRITE->Draw(*TabCenterTex, &rcTag, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->SetTransform(&TabRightMat);
	SPRITE->Draw(*TabRightTex, &rcTag, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

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
		rcItemDes = { 0,200 * cursor,650,200 * cursor + 200 };
	}
	if (BaitTextFlg) {
		rcItemNameText = { 500,0,1000,720 };
		//カーソル位置に応じてアイテム説明変
		rcItemDes = { 650,200 * cursor,1300,200 * cursor + 200 };
	}
	if (ReelTextFlg) {
		rcItemNameText = { 1000,0,1500,720 };
		//カーソル位置に応じてアイテム説明変更
		rcItemDes = { 1300,200 * cursor,1950,200 * cursor + 200 };
	}
	SPRITE->SetTransform(&ItemNameTextMat);
	SPRITE->Draw(*ItemNameTextTex, &rcItemNameText, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	SPRITE->SetTransform(&ItemDesMat);
	SPRITE->Draw(*ItemDesTex, &rcItemDes, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//売り切れ
	RECT rcSoldOut = { 0,0,50,50 };
	for (int i = 0; i < LISTNUMBER; i++) {
		for (int j = 0; j < TAB; j++) {
			SPRITE->SetTransform(&SoldOutMat[j][i]);
			SPRITE->Draw(*SoldOutTex, &rcSoldOut, &D3DXVECTOR3(25.0f, 25.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}


	RECT rcE_Power = { 0,0,350,39 };
	SPRITE->SetTransform(&E_PowerMat);
	SPRITE->Draw(*E_PowerTex, &rcE_Power, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcMoneyFrame = { 0,0,400,70 };
	SPRITE->SetTransform(&MoneyFrameMat);
	SPRITE->Draw(*MoneyFrameTex, &rcMoneyFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//エサ
	RECT rcBait;
	if (BaitTextFlg) {
		rcBait = { 300 * cursor, 0,300 * cursor + 300, 328 };
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
