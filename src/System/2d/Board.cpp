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

			//�|���̒��S�_���Ίp���̌�_�ɂȂ�悤�ɔz�u���Ă���
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


//�|���̕\��
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
			//�T�C�Y�����ɑΊp���𒆐S�Ƃ������W�ɕϊ�
			tmp.v[0].Pos = D3DXVECTOR3(-(Size->x * 0.5), (Size->y * 0.5), (Size->z * 0.5));
			tmp.v[1].Pos = D3DXVECTOR3((Size->x * 0.5), (Size->y * 0.5), (Size->z * 0.5));
			tmp.v[2].Pos = D3DXVECTOR3((Size->x * 0.5), -(Size->y * 0.5), -(Size->z * 0.5));
			tmp.v[3].Pos = D3DXVECTOR3(-(Size->x * 0.5), -(Size->y * 0.5), -(Size->z * 0.5));
			//�F���w��
			tmp.v[0].Color = mColor;
			tmp.v[1].Color = mColor;
			tmp.v[2].Color = mColor;
			tmp.v[3].Color = mColor;
			//���S���W���w��(�����ڂ�*�|���̃T�C�Y+�I�t�Z�b�g)
			tmp.vPos = D3DXVECTOR3(Size->x * Side + OffSet->x, Size->y + OffSet->y, Size->z * Virtical + OffSet->z);

			D3DXMatrixTranslation(&tmp.vMat, tmp.vPos.x, tmp.vPos.y, tmp.vPos.z);
			mList.emplace_back(tmp);
		}
	}
}


