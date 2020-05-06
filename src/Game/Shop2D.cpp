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
	//���X�g
	FrameTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrame.png");
	D3DXMatrixTranslation(&FrameMat, 50.0f, 0.0f, 0.0f);
	fTextTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText.png");
	D3DXMatrixTranslation(&fTextMat, 50.0f, 0.0f, 0.0f);
	fTextSecTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText2.png");
	D3DXMatrixTranslation(&fTextSecMat, 50.0f, 0.0f, 0.0f);
	fTextSrdTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameText3.png");
	D3DXMatrixTranslation(&fTextSrdMat, 50.0f, 0.0f, 0.0f);

	//�^�u
	TabLeftTex   = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab1.png");
	TabCenterTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab2.png");
	TabRightTex  = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopFrameTab3.png");
	D3DXMatrixTranslation(&TabLeftMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&TabRightMat, 50.0f, 0.0f, 0.0f);
	tabL = 30;
	tabC = 0;
	tabR = 0;

	//�I���J�[�\��
	ListSelectTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ListSelect.png");
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[0], 0.0f);
}

void Shop2D::Update()
{
	//�㉺�L�[�ŃJ�[�\���ړ�
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

	//���E�L�[�Ń^�u�ړ�
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

	//�I���J�[�\��
	for (int i = 0; i < LISTNUMBER; i++) {
		select[i] = i * 60.5f;
	}
	D3DXMatrixTranslation(&ListSelectMat, 50.0f, select[cursor], 0.0f);
	//�^�u
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
	D3DXMatrixTranslation(&TabLeftMat,   50.0f, 0.0f - tabL, 0.0f);
	D3DXMatrixTranslation(&TabCenterMat, 50.0f, 0.0f - tabC, 0.0f);
	D3DXMatrixTranslation(&TabRightMat,  50.0f, 0.0f - tabR, 0.0f);
}

void Shop2D::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	//�^�O
	RECT rcTagL = { 0,0,500,720 };
	SPRITE->SetTransform(&TabLeftMat);
	SPRITE->Draw(TabLeftTex, &rcTagL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagC = { 0,0,500,720 };
	SPRITE->SetTransform(&TabCenterMat);
	SPRITE->Draw(TabCenterTex, &rcTagC, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTagR = { 0,0,500,720 };
	SPRITE->SetTransform(&TabRightMat);
	SPRITE->Draw(TabRightTex, &rcTagR, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//���X�g
	RECT rcFrame = { 0,0,500,720 };
	SPRITE->SetTransform(&FrameMat);
	SPRITE->Draw(FrameTex, &rcFrame, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//�I���J�[�\��
	RECT rcSelect = { 0,0,500,720 };
	SPRITE->SetTransform(&ListSelectMat);
	SPRITE->Draw(ListSelectTex, &rcSelect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//���X�g����
	RECT rcText = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextMat);
	if(RodTextFlg)	SPRITE->Draw(fTextTex, &rcText, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTextSec = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextSecMat);
	if(BaitTextFlg) SPRITE->Draw(fTextSecTex, &rcTextSec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcTextSrd = { 0,0,500,720 };
	SPRITE->SetTransform(&fTextSrdMat);
	if (ReelTextFlg) SPRITE->Draw(fTextSrdTex, &rcTextSec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	SPRITE->End();
}

void Shop2D::Draw3D()
{
}

int Shop2D::SetListChange()
{
	return tabPattern;
}
