#pragma once
#include"stBord.h"
//struct stBordProto;
class Bord
{
protected:


	
	void CleateBordList(std::vector<std::vector<stBordProto>> &List, int cnt,int  cnt2);

	void Set4VartexPos(std::vector<std::vector<stBordProto>>&List,const D3DXVECTOR3 &Vec,const D3DCOLOR& argb);

	void SetTex(std::vector<std::vector<stBordProto>>&List,bool Flg);


};

