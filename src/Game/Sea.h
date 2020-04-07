#pragma once
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// 頂点フォーマットの定義
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};

class Sea 
{
public:
	Sea();
	~Sea();


	void Init(void);
	void Update(void);

	void Draw();

	float Ray_Judge(D3DXVECTOR3 Pos);

	void setTexParam(std::string Path, int W, int H, D3DCOLOR color) {
		mPath = Path;
		mW = W;
		mH = H;
		mColor = color;
	}


private:

VERTEX v[4];//板ポリ一枚分
D3DXMATRIX vMat;
LPDIRECT3DTEXTURE9 vTex;

//テクスチャ関係の変数
std::string mPath = "";
int mW = 0, mH = 0;
D3DCOLOR mColor = 0;


const int SIDE = 20;
const int VIRTICAL = 20;

float Height[21][21];
};