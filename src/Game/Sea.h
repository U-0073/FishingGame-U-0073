#pragma once
#include"../System/2d/Board.h"

class Sea : Board
{
public:
	Sea();
	~Sea();



	void Draw();

	float Ray_Judge(D3DXVECTOR3 Pos);


private:


	LPDIRECT3DTEXTURE9 vTex;



const int SIDE = 20;
const int VIRTICAL = 20;

float Height[21][21];
};