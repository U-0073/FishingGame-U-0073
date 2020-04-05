#pragma once
#include"VerTex.h"

struct stBordProto
{
	VERTEX	v[4];

	D3DXVECTOR2	DrawSize;
	D3DXMATRIX	Mat;
	D3DXVECTOR3	Pos;

	D3DXMATRIX RoMat;
	D3DXVECTOR3 Angle;

};