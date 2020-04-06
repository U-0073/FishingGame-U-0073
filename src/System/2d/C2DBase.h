#pragma once
#include"VerTex.h"

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//struct VERTEX;
class C2DBase
{

protected:

	
	void Draw1(D3DXMATRIX	&Mat, LPDIRECT3DTEXTURE9 LoadTex, VERTEX *v, const LPDIRECT3DDEVICE9 lpD3DDevice);
	void Draw2(RECT rc, D3DXMATRIX &Mat, LPDIRECT3DTEXTURE9 &LoadTex, const LPD3DXSPRITE lpSprite);
	void SafeRereace(LPDIRECT3DTEXTURE9 &LoadTex);

	void LoadTexture(LPDIRECT3DDEVICE9 lpD3DDevice, LPDIRECT3DTEXTURE9 *lpTex, const std::string & Path, int W, int H, const D3DCOLOR Color)
	{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(lpD3DDevice, Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);

	}
	
	
};

