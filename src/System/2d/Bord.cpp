
//#include"C2DBase.h"

#include"../KdLibrary/KdLibrary.h"
#include "Bord.h"

Bord::Bord()
{
}

//�|���̕\��
void Bord::Draw()
{
	for (int siz1 = 0; siz1 < mList.size(); siz1++) {
		for (int siz2 = 0; siz2 < mList[siz1].size(); siz2++) {
			KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
			KD3D.GetDev()->SetTransform(D3DTS_WORLD, &mList[siz1].at(siz2).Mat);
			KD3D.GetDev()->SetTexture(0, RESOURCE_MNG.GetTexture(mPath,mW,mH,mColor));

			KD3D.GetDev()->SetFVF(FVF_VERTEX);
			KD3D.GetDev()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, /*�|���S����*/2, /*���_�̕ϐ�*/mList[siz1].at(siz2).v, sizeof(VERTEX));
			KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}



void Bord::SafeRereace(LPDIRECT3DTEXTURE9& LoadTex)
{
	if (LoadTex != nullptr) {
		LoadTex->Release();
	}
}


//�����|���̐���
void Bord::CleateBordList(int cnt,int cnt2)
{
	
	std::vector<std::vector<stBord>>mList(cnt, std::vector<stBord>(cnt2));

	
}


void Bord::Update()
{
	//std::vector<std::vector<stBordProto>>::iterator itr_b ;
	//std::vector<stBordProto>::iterator itr_bb ;
	//
	for (int siz1 = 0; siz1 < mList.size(); siz1++) {
		for (int siz2 = 0; siz2 < mList[siz1].size(); siz2 ++ ) {

			mList[siz1].at(siz2).v[0].Pos = D3DXVECTOR3(-(mSize.x*0.5), (mSize.y * 0.5), (mSize.z * 0.5));
			mList[siz1].at(siz2).v[1].Pos = D3DXVECTOR3((mSize.x * 0.5), (mSize.y * 0.5), (mSize.z * 0.5));
			mList[siz1].at(siz2).v[2].Pos = D3DXVECTOR3((mSize.x * 0.5), -(mSize.y * 0.5), -(mSize.z * 0.5));
			mList[siz1].at(siz2).v[3].Pos = D3DXVECTOR3(-(mSize.x * 0.5), -(mSize.y * 0.5), -(mSize.z * 0.5));


			mList[siz1].at(siz2).v[0].Color = mColor;
			mList[siz1].at(siz2).v[1].Color = mColor;
			mList[siz1].at(siz2).v[2].Color = mColor;
			mList[siz1].at(siz2).v[3].Color = mColor;
		
		

		
			mList[siz1].at(siz2).Pos = D3DXVECTOR3((mSize.x * siz1) - 0, -0.9, (mSize.z * siz2) -0);
			D3DXMatrixTranslation(&mList[siz1].at(siz2).Mat, mList[siz1].at(siz2).Pos.x, mList[siz1].at(siz2).Pos.y, mList[siz1].at(siz2).Pos.z);
	
		}
	}
	//�␳==========================================================
	//if (Row_Column.x == 0)Row_Column.x = 1;
	//if (Row_Column.y == 0)Row_Column.y = 1;
	

	//==============================================================
	//for (int i=0; itr_b < itr_e; itr_b++,i++) {
		
		/*
		List.at(i).v[0].Tex = D3DXVECTOR2((i%(int)Row_Column.x), i / (int)Row_Column.y);
		List.at(i).v[1].Tex = D3DXVECTOR2((i+1) % (int)Row_Column.x, i / (int)Row_Column.y);
		List.at(i).v[2].Tex = D3DXVECTOR2(i % (int)Row_Column.x, (i + 1) / (int)Row_Column.y);
		List.at(i).v[3].Tex = D3DXVECTOR2((i + 1) % (int)Row_Column.x, (i + 1) / (int)Row_Column.y);
		*/
	//}

}
//�e�N�X�`���̕����\��t��
void Bord::SetTex(bool Flg/*tue=����*/)//
{
	for (int siz1 = 0; siz1 < mList.size(); siz1++) {
		for (int siz2 = 0; siz2 < mList[siz1].size(); siz2++) {
			if (Flg) {
				mList[siz1].at(siz2).v[0].Tex = D3DXVECTOR2(siz1 /(float) mList.size(), siz2 / (float)mList.size());
				mList[siz1].at(siz2).v[1].Tex = D3DXVECTOR2((siz1+1) / (float)mList.size(), siz2 / (float)mList.size());
				mList[siz1].at(siz2).v[2].Tex = D3DXVECTOR2(siz1/ (float)mList.size(), (siz2+1) / (float)mList.size());
				mList[siz1].at(siz2).v[3].Tex = D3DXVECTOR2(siz1 / (float)mList.size(), (siz2+1) / (float)mList.size());

			}
			else {
				mList[siz1].at(siz2).v[0].Tex = D3DXVECTOR2(0, 0);
				mList[siz1].at(siz2).v[1].Tex = D3DXVECTOR2(1, 0);
				mList[siz1].at(siz2).v[2].Tex = D3DXVECTOR2(1, 1);
				mList[siz1].at(siz2).v[3].Tex = D3DXVECTOR2(0, 1);
			}
		
		}

	}
}

