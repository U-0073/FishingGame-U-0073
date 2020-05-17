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
	//リスト
	FrameTex = *RESOURCE_MNG.GetTexture("Shop/ShopFrame.png");
	D3DXMatrixTranslation(&FrameMat, 50.0f, 0.0f, 0.0f);

	ItemNameTextTex = *RESOURCE_MNG.GetTexture("Shop/ShopFrameText0.png");
	D3DXMatrixTranslation(&ItemNameTextMat, 50.0f, 0.0f, 0.0f);

	//アイテム説明枠
	ItemDesFrameTex = *RESOURCE_MNG.GetTexture("Shop/ItemDescriptionFrame.png");
	D3DXMatrixTranslation(&ItemDesFrameMat, 575.0f, 465.0f, 0.0f);
	
	//エサ
	BaitTex = *RESOURCE_MNG.GetTexture("Shop/Bait.png");
	D3DXMatrixTranslation(&BaitMat, 735.0f, 125.0f, 0.0f);

	//タブ
	TabLeftTex = *RESOURCE_MNG.GetTexture("Shop/ShopFrameTab1.png");
	TabCenterTex = *RESOURCE_MNG.GetTexture("Shop/ShopFrameTab2.png");
	TabRightTex = *RESOURCE_MNG.GetTexture("Shop/ShopFrameTab3.png");
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f, 0.0f);
	tabL = 30;
	tabC = 0;
	tabR = 0;

	//選択カーソル
	ListSelectTex = *RESOURCE_MNG.GetTexture("Shop/ListSelect.png");
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[0], 0.0f);
}

void Shop2D::Update()
{
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

	//選択カーソル
	for (int i = 0; i < LISTNUMBER; i++) {
		select[i] = i * 60.5f;
	}
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[cursor], 0.0f);
	//タブ
	if (tabPattern == 0) {
		tabL = 40; tabC = 0; tabR = 0;
		RodTextFlg = true;
		BaitTextFlg = false;
		ReelTextFlg = false;
	}
	if (tabPattern == 1) {
		tabL = 0; tabC = 40; tabR = 0;
		RodTextFlg = false;
		BaitTextFlg = true;
		ReelTextFlg = false;
	}
	if (tabPattern == 2) {
		tabL = 0; tabC = 0; tabR = 40;
		RodTextFlg = false;
		BaitTextFlg = false;
		ReelTextFlg = true;
	}
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f - tabL, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f - tabC, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f - tabR, 0.0f);
}

void Shop2D::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//タグ
	RECT rcTagL = { 0,0,500,720 };
	SPRITE->SetTransform(&TabLeftMat);
	SPRITE->Draw(TabLeftTex, &rcTagL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagC = { 0,0,500,720 };
	SPRITE->SetTransform(&TabCenterMat);
	SPRITE->Draw(TabCenterTex, &rcTagC, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagR = { 0,0,500,720 };
	SPRITE->SetTransform(&TabRightMat);
	SPRITE->Draw(TabRightTex, &rcTagR, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//リスト
	RECT rcFrame = { 0,0,500,720 };
	SPRITE->SetTransform(&FrameMat);
	SPRITE->Draw(FrameTex, &rcFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//アイテム説明枠
	RECT rcItemDesFrame = { 0,0,650,200 };
	SPRITE->SetTransform(&ItemDesFrameMat);
	SPRITE->Draw(ItemDesFrameTex, &rcItemDesFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//選択カーソル
	RECT rcSelect = { 0,0,500,720 };
	SPRITE->SetTransform(&ListSelectMat);
	SPRITE->Draw(ListSelectTex, &rcSelect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//リスト文字
	RECT rcItemNameText;
	if (RodTextFlg) {
		rcItemNameText = { 0,0,500,720 };
	}
	if (BaitTextFlg) {
		rcItemNameText = { 500,0,1000,720 };
	}
	if (ReelTextFlg){
		rcItemNameText = { 1000,0,1500,720 };
	}
	SPRITE->SetTransform(&ItemNameTextMat);
	SPRITE->Draw(ItemNameTextTex, &rcItemNameText, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	

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
		SPRITE->Draw(BaitTex, &rcBait, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	SPRITE->End();
}

void Shop2D::Draw3D()
{
}

void Shop2D::End()
{
	m_pModel = nullptr;
	SafeReleaseTex(FrameTex);
	SafeReleaseTex(ItemNameTextTex);

	BaitTex->Release();

	SafeReleaseTex(TabLeftTex);
	SafeReleaseTex(TabCenterTex);
	SafeReleaseTex(TabRightTex);

	SafeReleaseTex(ListSelectTex);
	SafeReleaseTex(ItemDesFrameTex);
}

int Shop2D::SetListChange()
{
	return tabPattern;
}
