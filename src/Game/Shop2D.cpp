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
	//今持ってるアイテムの確認
	BuyItem = DTWHOUCE.GetVec("Buy");

	//アイテムの情報
	RodStatus[0].x = 1000;
	RodStatus[1].x = 2500;
	RodStatus[2].x = 4000;
	RodStatus[3].x = 10000;
	RodStatus[4].x = 20000;
	RodStatus[5].x = 50000;
	RodStatus[6].x = 100000;
	RodStatus[7].x = 100000000;
	BaitStatus[0].x = 100;
	BaitStatus[1].x = 200;
	BaitStatus[2].x = 500;
	BaitStatus[3].x = 800;
	BaitStatus[4].x = 1000;
	BaitStatus[5].x = 3000;
	BaitStatus[6].x = 5000;
	BaitStatus[7].x = 50000000;
	ReelStatus[0].x = 1000;
	ReelStatus[1].x = 2000;
	ReelStatus[2].x = 2500;
	ReelStatus[3].x = 4000;
	ReelStatus[4].x = 10000;
	ReelStatus[5].x = 20000;
	ReelStatus[6].x = 50000;
	ReelStatus[7].x = 999999999;
	//性能
	RodStatus[0].y = 5;
	RodStatus[1].y = 7;
	RodStatus[2].y = 10;
	RodStatus[3].y = 15;
	RodStatus[4].y = 20;
	RodStatus[5].y = 30;
	RodStatus[6].y = 50;
	RodStatus[7].y = 99;
	BaitStatus[0].y = 1;
	BaitStatus[1].y = 2;
	BaitStatus[2].y = 4;
	BaitStatus[3].y = 6;
	BaitStatus[4].y = 10;
	BaitStatus[5].y = 15;
	BaitStatus[6].y = 30;
	BaitStatus[7].y = 99;
	ReelStatus[0].y = 5;
	ReelStatus[1].y = 8;
	ReelStatus[2].y = 10;
	ReelStatus[3].y = 15;
	ReelStatus[4].y = 20;
	ReelStatus[5].y = 30;
	ReelStatus[6].y = 50;
	ReelStatus[7].y = 99;
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

	//購入関係ウィンドウ
	Can_tBuyTex = RESOURCE_MNG.GetTexture("Shop/Can'tBuy.png");
	Can_tBuyMat.SetTrans(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f);


	BuyItem.x = 0;
	BuyItem.y = 0;
	BuyItem.z = 0;
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

		//所持金が足りないとき
		if ((Possession < RodStatus[cursor].x) || (Possession < BaitStatus[cursor].x) || (Possession < ReelStatus[cursor].x)) {
			Can_tBuyFlg = true;
		}
		//足りるとき
		else {
			//釣り竿
			if (tabPattern == 0) {
				//開放してたら
				if (BuyItem.x == cursor) {
					Possession -= RodStatus[cursor].x;
					BuyItem.x++;
					AllStatus += RodStatus[cursor].y;
				}
				//未開放
				else if (BuyItem.x < cursor)NotOpenFlg = true;
				//購入済み
				else if (BuyItem.x > cursor)BuyFlg = true;
			}
			//エサ
			if (tabPattern == 1) {
				//開放してたら
				if (BuyItem.y == cursor) {
					Possession -= BaitStatus[cursor].x;
					BuyItem.y++;
					AllStatus += BaitStatus[cursor].y;
				}
				//未開放
				else if (BuyItem.y < cursor)NotOpenFlg = true;
				//購入済み
				else if (BuyItem.y > cursor)BuyFlg = true;
			}
			//リール
			if (tabPattern == 2) {
				//開放してたら
				if (BuyItem.z == cursor) {
					Possession -= ReelStatus[cursor].x;
					BuyItem.z++;
					AllStatus += ReelStatus[cursor].y;
				}
				//未開放
				else if (BuyItem.y < cursor)NotOpenFlg = true;
				//購入済み
				else if (BuyItem.y > cursor)BuyFlg = true;
			}
		}
		//各アイテムの性能値を計算して送る
		AllStatus = (AllStatus / 3.0f) / 100.0f;
		DTWHOUCE.SetNo("Quality", AllStatus);
		WindowPattern = 0;
		EnterFlg = false;
	}
	//
	if (Possession <= 0) {
		Possession = 0;
	}
	//所持金足りません
	if (Can_tBuyFlg) {
		ctCnt++;
		if (ctCnt >= 60) {
			Can_tBuyFlg = false;
			ctCnt = 0;
		}
	}
	//開放されてません
	if (NotOpenFlg) {
		noCnt++;
		if (noCnt >= 60) {
			NotOpenFlg = false;
			noCnt = 0;
		}
	}
	//もう持ってます
	if (BuyFlg) {
		byCnt++;
		if (byCnt >= 60) {
			BuyFlg = false;
			byCnt = 0;
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

	//今、釣り竿、エサ、リールを上から何番目まで買ったかを保存する
	DTWHOUCE.SetVec("Buy", BuyItem);
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
		//釣り竿
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
		transMat.SetTrans(-35, 0, 0);
		int i;
		for (i = 0; cScore[i] != '\0'; i++);
		for (i -= 1; i >= 0; i--) {
			numberMat *= transMat;
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
