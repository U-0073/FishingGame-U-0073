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


	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex;
	std::shared_ptr<KdModel>vModel;


const int SIDE = 100;
const int VIRTICAL = 100;

float Height[101][101];
};