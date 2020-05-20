#pragma once
#include"../System/FrameBase/GameObject.h"



class Title : GameObject
{
public:
	Title();
	~Title();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex = nullptr;
	D3DXMATRIX mMat;//タイトル
	D3DXVECTOR3 mPos;

	D3DXMATRIX mMat2;//エンターキー
	D3DXVECTOR3 mPos2;
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex2 = nullptr;

	//anime
	std::shared_ptr<LPDIRECT3DTEXTURE9> titleAnime = nullptr;
	std::shared_ptr<LPDIRECT3DTEXTURE9> whiteAnime = nullptr;
	KdMatrix animMat;
	KdMatrix wAnim;
	int animAlpha;
	bool animFlg;

	int alpha;

};

