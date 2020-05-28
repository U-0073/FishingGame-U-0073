#pragma once
#include"../System/FrameBase/GameObject.h"

#define LISTNUMBER 8
#define TAB 3


class Shop2D : GameObject
{
public:
	Shop2D();
	~Shop2D();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

	int SetTabPattern();
	int SetCursor();

private:

	KdMatrix FrameMat;
	KdMatrix ItemNameTextMat;
	KdMatrix ItemDesMat;
	KdMatrix TabLeftMat;
	KdMatrix TabCenterMat;
	KdMatrix TabRightMat;
	KdMatrix ListSelectMat;
	KdMatrix MoneyFrameMat;
	KdMatrix E_PowerMat;
	KdMatrix numberMat;
	KdMatrix transMat;
	KdMatrix statusMat;
	KdMatrix BaitMat;
	KdMatrix Can_tBuyMat;
	KdMatrix SoldOutMat[TAB][LISTNUMBER];
	KdVec3 BuyItem;		//�������Ă�A�C�e��
	KdVec3 OpenItem;	//��������Ă�A�C�e��

	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameSecTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> FrameSrdTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ItemNameTextTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ItemDesTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabLeftTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabCenterTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> TabRightTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> ListSelectTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> MoneyFrameTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> E_PowerTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> numberTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> statusTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> BaitTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> Can_tBuyTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> SoldOutTex;
	D3DXVECTOR3 mPos;

	//�A�C�e���̒l�i
	int RodPrice[8];
	int BaitPrice[8];
	int ReelPrice[8];
	//�J�[�\��
	int cursor = 0;
	int tabPattern = 0;
	//������
	int Possession;
	int num[10];
	//�E�B���h�E�p�^�[��
	int WindowPattern = 0;
	int ctCnt = 0;

	float select[LISTNUMBER];
	float tabL = 0, tabC = 0, tabR = 0;

	bool KeyDownFlg = false;
	bool KeyUpFlg = false;
	bool KeyRightFlg = false;
	bool KeyLeftFlg = false;
	bool RodTextFlg = false;
	bool BaitTextFlg = false;
	bool ReelTextFlg = false;
	bool EnterFlg = false;
	bool EnterDownFlg = false;
	bool Can_tBuyFlg = false;

	//���\�l
	float Quality[3];
};

