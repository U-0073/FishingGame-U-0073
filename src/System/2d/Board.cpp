#include"../KdLibrary/KdLibrary.h"
#include "Board.h"

Board::Board()
{
}

Board::~Board()
{
}


void Board::Update(const int* Side, const int* Virtical)
{
	for (int siz1 = 0; siz1 < *Side; siz1++) {
		for (int siz2 = 0; siz2 < *Virtical; siz2++) {

			//板ポリの中心点が対角線の交点になるように配置している
			v[0].Pos = D3DXVECTOR3(-(mSize.x * 0.5), (mSize.y * 0.5), (mSize.z * 0.5));
			v[1].Pos = D3DXVECTOR3((mSize.x * 0.5), (mSize.y * 0.5), (mSize.z * 0.5));
			v[2].Pos = D3DXVECTOR3((mSize.x * 0.5), -(mSize.y * 0.5), -(mSize.z * 0.5));
			v[3].Pos = D3DXVECTOR3(-(mSize.x * 0.5), -(mSize.y * 0.5), -(mSize.z * 0.5));


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
}


void Board::SafeRelease(LPDIRECT3DTEXTURE9& LoadTex)
{
	if (LoadTex != nullptr) {
		LoadTex->Release();
	}
}

void Board::CreateBoard(int Side, int Virtical, D3DXVECTOR3* Size, D3DXVECTOR3* OffSet)
{
	for (int i = 0; i < Side; i++) {
		for (int j = 0; j < Virtical; j++) {
			stBoard tmp;
			//サイズを元に対角線を中心とした座標に変換
			tmp.v[0].Pos = D3DXVECTOR3(-(Size->x * 0.5), (Size->y * 0.5), (Size->z * 0.5));
			tmp.v[1].Pos = D3DXVECTOR3((Size->x * 0.5), (Size->y * 0.5), (Size->z * 0.5));
			tmp.v[2].Pos = D3DXVECTOR3((Size->x * 0.5), -(Size->y * 0.5), -(Size->z * 0.5));
			tmp.v[3].Pos = D3DXVECTOR3(-(Size->x * 0.5), -(Size->y * 0.5), -(Size->z * 0.5));
			//色を指定
			tmp.v[0].Color = mColor;
			tmp.v[1].Color = mColor;
			tmp.v[2].Color = mColor;
			tmp.v[3].Color = mColor;
			//中心座標を指定(何枚目か*板ポリのサイズ+オフセット)
			tmp.vPos = D3DXVECTOR3(Size->x * Side + OffSet->x, Size->y + OffSet->y, Size->z * Virtical + OffSet->z);

			D3DXMatrixTranslation(&tmp.vMat, tmp.vPos.x, tmp.vPos.y, tmp.vPos.z);
			mList.emplace_back(tmp);
		}
	}
}


