#include"../System/KdLibrary/KdLibrary.h"
#include"Result.h"


Result::Result()
{
}

Result::~Result()
{
}


void Result::Init() 
{
	vTex = RESOURCE_MNG.GetTexture("board.png", 1000, 430, NULL);
	mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);

}

void Result::Update()
{
	mPos = D3DXVECTOR3(1280.0f/2, 720.0f/3*2.3, 0.0f);
	D3DXMatrixTranslation(&mMat, mPos.x, mPos.y, mPos.z);

}

void Result::Draw2D()
{
	RECT rcBoard = { 0,0,1000,380 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(*vTex, &rcBoard, &D3DXVECTOR3(1000.0f/2, 380.0f/2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void Result::Draw3D()
{
}

void Result::End()
{
	vTex = nullptr;
}

