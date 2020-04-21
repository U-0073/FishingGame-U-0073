#pragma once
#include"../System/2d/Board.h"

class Sea : Board
{
public:
	Sea();
	~Sea();



	void Draw();
	void DrawObject();

	float Ray_Judge(D3DXVECTOR3 Pos);


private:


	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex;
	std::shared_ptr<KdModel>m_pModel;
	D3DXMATRIX m_world;

const int SIDE = 100;
const int VIRTICAL = 100;

float Height[101][101];
};