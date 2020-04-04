#pragma once



class CGameScene
{
public:
    CGameScene( LPDIRECT3DDEVICE9 lpD3DDevice ) ;
    ~CGameScene();

    void Update();
    void Draw2D( LPDIRECT3DDEVICE9 lpD3DDevice );
    void Draw3D( LPDIRECT3DDEVICE9 lpD3DDevice );

private:

    void LoadTexture(LPDIRECT3DDEVICE9 lpD3DDevice,LPDIRECT3DTEXTURE9 *lpTex, const std::string & Path, const int W,  const int H,const D3DCOLOR Color);

    LPD3DXSPRITE	mpSprite;	// スプライト
    LPD3DXFONT		mpFont;		// フォント

};

