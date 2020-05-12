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
	m_pModel = nullptr;
	SafeReleaseTex(FrameTex);
	SafeReleaseTex(fTextTex);
	SafeReleaseTex(fTextSecTex);
	SafeReleaseTex(fTextSrdTex);

	for (int i = 0; i < LISTNUMBER; i++) {
		BaitTex[i]->Release();
	}

	SafeReleaseTex(TabLeftTex);
	SafeReleaseTex(TabCenterTex);
	SafeReleaseTex(TabRightTex);

	SafeReleaseTex(ListSelectTex);
}

void Shop2D::Init()
{
	//リスト
	FrameTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrame.png");
	D3DXMatrixTranslation(&FrameMat, 50.0f, 0.0f, 0.0f);
	fTextTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText.png");
	D3DXMatrixTranslation(&fTextMat, 50.0f, 0.0f, 0.0f);
	fTextSecTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText2.png");
	D3DXMatrixTranslation(&fTextSecMat, 50.0f, 0.0f, 0.0f);
	fTextSrdTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText3.png");
	D3DXMatrixTranslation(&fTextSrdMat, 50.0f, 0.0f, 0.0f);

	//エサ
	BaitTex[0] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait1.png");
	BaitTex[1] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait2.png");
	BaitTex[2] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait3.png");
	BaitTex[3] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait4.png");
	BaitTex[4] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait5.png");
	BaitTex[5] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait6.png");
	BaitTex[6] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait7.png");
	BaitTex[7] = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/Bait8.png");
	for (int i = 0; i < LISTNUMBER; i++) {
		D3DXMatrixTranslation(&BaitMat[i], 725.0f, 125.0f, 0.0f);
	}

	//タブ
	TabLeftTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab1.png");
	TabCenterTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab2.png");
	TabRightTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab3.png");
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f, 0.0f);
	tabL = 30;
	tabC = 0;
	tabR = 0;

	//選択カーソル
	ListSelectTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ListSelect.png");
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

	//選択カーソル
	RECT rcSelect = { 0,0,500,720 };
	SPRITE->SetTransform(&ListSelectMat);
	SPRITE->Draw(ListSelectTex, &rcSelect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//リスト文字
	RECT rcText = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextMat);
	if (RodTextFlg)	SPRITE->Draw(fTextTex, &rcText, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTextSec = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextSecMat);
	if (BaitTextFlg) SPRITE->Draw(fTextSecTex, &rcTextSec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTextSrd = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextSrdMat);
	if (ReelTextFlg) SPRITE->Draw(fTextSrdTex, &rcTextSec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//エサ
	for (int i = 0; i < LISTNUMBER; i++) {
		rcBait[i] = { 0,0,300,328 };
		SPRITE->SetTransform(&BaitMat[i]);
	}

	switch (cursor)
	{
	case 0:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[0], &rcBait[0], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 1:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[1], &rcBait[1], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 2:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[2], &rcBait[2], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 3:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[3], &rcBait[3], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 4:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[4], &rcBait[4], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 5:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[5], &rcBait[5], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 6:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[6], &rcBait[6], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 7:
		if (BaitTextFlg) SPRITE->Draw(BaitTex[7], &rcBait[7], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}

	SPRITE->End();
}

void Shop2D::Draw3D()
{
}

int Shop2D::SetListChange()
{
	return tabPattern;
}
