#pragma once
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 頂点情報の定義
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};


//頂点4点で板ポリ一枚を構成する
struct stBoard {
	VERTEX	v[4];

	//D3DXVECTOR2	DrawSize;
	D3DXMATRIX	Mat;
	D3DXVECTOR3	Pos;
};

class Board
{

private:
	std::vector<std::vector<stBoard>> mList;
	//テクスチャ関係の変数
	std::string mPath = "";
	int mW = 0, mH = 0;
	D3DCOLOR mColor = 0;

	D3DXVECTOR3 mSize{ 1,1,1 };


public:
	Board();
	void Draw();
	void SafeRelease(LPDIRECT3DTEXTURE9& LoadTex);

	void setTexParam(std::string Path, int W, int H, D3DCOLOR color, bool flg) {
		mPath = Path;
		mW = W;
		mH = H;
		mColor = color;
		SetTex(flg);
	}

	void ChangeSize(D3DXVECTOR3 size) { mSize = size; }

	void CleateBoardList(int cnt, int  cnt2);

	void Update();

private:
	void SetTex(bool Flg);


};

