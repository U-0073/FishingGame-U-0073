#include"VerTex.h"
//#include"C2DBase.h"

#include <vector>
#include<d3dx9.h>

#include "Bord.h"


//複数板ポリの管理
void Bord::CleateBordList(std::vector<std::vector<stBordProto>> &_List,int cnt,int cnt2)
{
	
	std::vector<std::vector<stBordProto>> List(cnt, std::vector<stBordProto>(cnt2));
	_List = List;
	
}


void Bord::Set4VartexPos(std::vector<std::vector<stBordProto>>&List,const D3DXVECTOR3 &Vec, const D3DCOLOR& argb)
{
	//std::vector<std::vector<stBordProto>>::iterator itr_b ;
	//std::vector<stBordProto>::iterator itr_bb ;
	//
	for (int siz1 = 0; siz1 < List.size(); siz1++) {
		for (int siz2 = 0; siz2 < List[siz1].size(); siz2 ++ ) {

			List[siz1].at(siz2).v[0].Pos = D3DXVECTOR3(-(Vec.x / 2.0f), (Vec.y / 2.0f), (Vec.z / 2.0f));
			List[siz1].at(siz2).v[1].Pos = D3DXVECTOR3((Vec.x / 2.0f), (Vec.y / 2.0f), (Vec.z / 2.0f));
			List[siz1].at(siz2).v[2].Pos = D3DXVECTOR3((Vec.x / 2.0f), -(Vec.y / 2.0f), -(Vec.z / 2.0f));
			List[siz1].at(siz2).v[3].Pos = D3DXVECTOR3(-(Vec.x / 2.0f), -(Vec.y / 2.0f), -(Vec.z / 2.0f));

			List[siz1].at(siz2).v[0].Color = argb;
			List[siz1].at(siz2).v[1].Color = argb;
			List[siz1].at(siz2).v[2].Color = argb;
			List[siz1].at(siz2).v[3].Color = argb;


		}
	}
	//補正==========================================================
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
//テクスチャの分割貼り付け
void Bord::SetTex(std::vector<std::vector<stBordProto>>& List,bool Flg/*tue=分割*/)//
{
	for (int siz1 = 0; siz1 < List.size(); siz1++) {
		for (int siz2 = 0; siz2 < List[siz1].size(); siz2++) {
			if (Flg) {
				List[siz1].at(siz2).v[0].Tex = D3DXVECTOR2(siz1 /(float) List.size(), siz2 / (float)List.size());
				List[siz1].at(siz2).v[1].Tex = D3DXVECTOR2((siz1+1) / (float)List.size(), siz2 / (float)List.size());
				List[siz1].at(siz2).v[2].Tex = D3DXVECTOR2(siz1/ (float)List.size(), (siz2+1) / (float)List.size());
				List[siz1].at(siz2).v[3].Tex = D3DXVECTOR2(siz1 / (float)List.size(), (siz2+1) / (float)List.size());

			}
			else {
				List[siz1].at(siz2).v[0].Tex = D3DXVECTOR2(0, 0);
				List[siz1].at(siz2).v[1].Tex = D3DXVECTOR2(1, 0);
				List[siz1].at(siz2).v[2].Tex = D3DXVECTOR2(1, 1);
				List[siz1].at(siz2).v[3].Tex = D3DXVECTOR2(0, 1);
			}
		
		}

	}
}

