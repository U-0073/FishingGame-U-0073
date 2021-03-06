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
	void Draw3D()override {};
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
	KdMatrix N_OpenMat;
	KdMatrix BuyMat;
	KdVec3 BuyItem;		//今持ってるアイテム
	
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
	std::shared_ptr<LPDIRECT3DTEXTURE9> N_OpenTex;
	std::shared_ptr<LPDIRECT3DTEXTURE9> BuyTex;
	D3DXVECTOR3 mPos;

	//アイテムの情報
	D3DXVECTOR2 RodStatus[8];
	D3DXVECTOR2 BaitStatus[8];
	D3DXVECTOR2 ReelStatus[8];
	float AllStatus = 0;
	//カーソル
	int cursor = 0;
	int tabPattern = 0;
	//所持金
	int Possession;
	int num[10];
	//ウィンドウパターン
	int WindowPattern = 0;
	int ctCnt = 0;
	int noCnt = 0;
	int byCnt = 0;

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
	bool BuyFlg = false;			//購入済みフラグ
	bool NotOpenFlg = false;		//未開放フラグ

	//性能値
	float Quality[3];
};

