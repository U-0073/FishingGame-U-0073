#include"../KdLibrary/KdLibrary.h"
#include "../FrameBase/CSceneBase.h"






CSceneBase::CSceneBase()

{





}


CSceneBase::~CSceneBase()
{

}

void CSceneBase::Update()
{


}

void CSceneBase::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);


	SPRITE->End();
}

void CSceneBase::Draw3D()
{
}

void CSceneBase::LoadTexture(LPDIRECT3DDEVICE9 lpD3DDevice, LPDIRECT3DTEXTURE9* lpTex, const std::string& Path, int W, int H, const D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(lpD3DDevice, Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);

}
