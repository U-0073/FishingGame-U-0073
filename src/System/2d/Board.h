#pragma once
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


class Board
{
public:
	Board();
	~Board();
	void SetSize();
	void SetArray();
	void Update(const int *Side, const int *Virtical);
	virtual void Draw() = 0;
	void SafeRelease(LPDIRECT3DTEXTURE9& LoadTex);

	virtual void setTexParam(std::string Path, int W, int H, D3DCOLOR color) 
	{
		mPath = Path;
		mW = W;
		mH = H;
		mColor = color;
	}



protected:
	std::vector<VERTEX> v;

	D3DXMATRIX vMat;
	//板ポリのサイズ
	D3DXVECTOR3 mSize = {1,1,1};

	//テクスチャ関係の変数
	std::string mPath = "";
	int mW = 0, mH = 0;
	D3DCOLOR mColor = 0;

};

