#pragma once


class CSceneBase
{
public:
	CSceneBase();
	~CSceneBase();

	virtual void Update();
	virtual void Draw2D();
	virtual void Draw3D();

private:

	void LoadTexture(LPDIRECT3DDEVICE9 lpD3DDevice, LPDIRECT3DTEXTURE9* lpTex, const std::string& Path, const int W, const int H, const D3DCOLOR Color);

	LPD3DXSPRITE	mpSprite;	// スプライト
	LPD3DXFONT		mpFont;		// フォント

};

