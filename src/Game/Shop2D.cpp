#include"../System/KdLibrary/KdLibrary.h"
#include"Shop2D.h"

Shop2D::Shop2D()
{
}

Shop2D::~Shop2D()
{
}

void Shop2D::Init()
{
	//枠
	FrameTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrame.png");
	D3DXMatrixTranslation(&FrameMat, 100.0f, 50.0f, 0.0f);

	//タブ
	TabLeftTex   = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab1.png");
	TabCenterTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab2.png");
	TabRightTex  = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab3.png");
	D3DXMatrixTranslation(&TabLeftMat, 100.0f, 100.0f, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 100.0f, 100.0f, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 100.0f, 100.0f, 0.0f);
	tabL = 30;
	tabC = 0;
	tabR = 0;

	//選択
	ListSelectTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ListSelect.png");
	D3DXMatrixTranslation(&ListSelectMat, 100.0f, select[0], 0.0f);

	for (int i = 0; i < 6; i++) {
		select[i] = 160 + (i * 67);
	}
	
	//リスト
	ListTex[0] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList1.png");
	ListTex[1] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList2.png");
	ListTex[2] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList3.png");
	ListTex[3] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList4.png");
	ListTex[4] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList5.png");
	ListTex[5] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopList6.png");	
	for (int i = 0; i < 6; i++) {
		D3DXMatrixTranslation(&ListMat[i], 100.0f, 150.0f, 0.0f);
	}
}

void Shop2D::Update()
{
	//上下キーでカーソル移動
	if (GetKey(VK_DOWN) & 0x8000) {
		if (KeyDownFlg == false) {
			cursor++;
			if (cursor >= 5)cursor = 5;
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
	D3DXMatrixTranslation(&ListSelectMat, 100.0f, select[cursor], 0.0f);
	//タブ
	if (tabPattern == 0) { tabL = 30; tabC = 0; tabR = 0; }
	if (tabPattern == 1) { tabL = 0; tabC = 30; tabR = 0; }
	if (tabPattern == 2) { tabL = 0; tabC = 0; tabR = 30; }
	D3DXMatrixTranslation(&TabLeftMat,   100.0f, 100.0f - tabL, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 100.0f, 100.0f - tabC, 0.0f);
	D3DXMatrixTranslation(&TabRightMat,  100.0f, 100.0f - tabR, 0.0f);
}

void Shop2D::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//タグ
	RECT rcTagL = { 0,0,500,600 };
	SPRITE->SetTransform(&TabLeftMat);
	SPRITE->Draw(TabLeftTex, &rcTagL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagC = { 0,0,500,600 };
	SPRITE->SetTransform(&TabCenterMat);
	SPRITE->Draw(TabCenterTex, &rcTagC, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagR = { 0,0,500,600 };
	SPRITE->SetTransform(&TabRightMat);
	SPRITE->Draw(TabRightTex, &rcTagR, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//枠
	RECT rcFrame = { 0,0,500,600 };
	SPRITE->SetTransform(&FrameMat);
	SPRITE->Draw(FrameTex, &rcFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//選択
	RECT rcSelect = { 0,0,500,100 };
	SPRITE->SetTransform(&ListSelectMat);
	SPRITE->Draw(ListSelectTex, &rcSelect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//文字
	RECT rcList[6];
	for (int i = 0; i < 6; i++) {
		rcList[i] = { 0,0,500,500 };
		SPRITE->SetTransform(&ListMat[i]);
		SPRITE->Draw(ListTex[i], &rcList[i], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SPRITE->End();
}

void Shop2D::Draw3D()
{
}