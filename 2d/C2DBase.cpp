#include "C2DBase.h"




//板ポリの表示
void C2DBase::Draw1(D3DXMATRIX & Mat, LPDIRECT3DTEXTURE9 LoadTex, VERTEX * v, const LPDIRECT3DDEVICE9 lpD3DDevice)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Mat);
	lpD3DDevice->SetTexture(0, LoadTex);

	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, /*ポリゴン数*/2, /*頂点の変数*/v, sizeof(VERTEX));
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//2?表示
void C2DBase::Draw2(RECT rc,D3DXMATRIX &Mat, LPDIRECT3DTEXTURE9 &LoadTex, const LPD3DXSPRITE lpSprite)
{
	

	
	lpSprite->SetTransform(&Mat);
	lpSprite->Draw(LoadTex, &rc, &D3DXVECTOR3(32, 32, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void C2DBase::SafeRereace(LPDIRECT3DTEXTURE9  &LoadTex)
{
	if (LoadTex != nullptr) {
		LoadTex->Release();
	}
}


