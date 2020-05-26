#include"../KdLibrary/KdLibrary.h"
#include "Board.h"

Board::Board()
{
	/*
	KdMatrix m;
	m._31 = scroll;
	KD3D.GetDev()->SetTransform(D3DTS_TEXTURE0, &m);

	KD3D.GetDev()->SetTransform(D3DTS_TEXTURE0, &KdMatrix());

	v.resize(???);
	ib.resize(???);
	*/
}

Board::~Board()
{
}


void Board::Update(const int* Side, const int* Virtical)
{
	for (int siz1 = 0; siz1 < *Side; siz1++) {
		for (int siz2 = 0; siz2 < *Virtical; siz2++) {

			//板ポリの中心点が対角線の交点になるように配置している
			v[0].Pos = D3DXVECTOR3(-(mSize.x * 0.5) * siz1, (mSize.y * 0.5), (mSize.z * 0.5)* siz2);
			v[1].Pos = D3DXVECTOR3((mSize.x * 0.5) * siz1, (mSize.y * 0.5), (mSize.z * 0.5) * siz2);
			v[2].Pos = D3DXVECTOR3((mSize.x * 0.5) * siz1, -(mSize.y * 0.5), -(mSize.z * 0.5) * siz2);
			v[3].Pos = D3DXVECTOR3(-(mSize.x * 0.5) * siz1, -(mSize.y * 0.5), -(mSize.z * 0.5) * siz2);


			v[0].Color = mColor;
			v[1].Color = mColor;
			v[2].Color = mColor;
			v[3].Color = mColor;




			//D3DXMatrixTranslation(&vMat, mList[siz1].at(siz2).Pos.x, mList[siz1].at(siz2).Pos.y, mList[siz1].at(siz2).Pos.z);

		}
	}
}


//板ポリの表示
void Board::Draw()
{
			KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
			KD3D.GetDev()->SetFVF(FVF_VERTEX);
			/*
			unsigned int index[] = { 0,7,8, 0,1,8,,,,, };
			KD3D.GetDev()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 21, 28, index, D3DFMT_D32, , );
			*/
}


void Board::SafeRelease(LPDIRECT3DTEXTURE9& LoadTex)
{
	if (LoadTex != nullptr) {
		LoadTex->Release();
	}
}

