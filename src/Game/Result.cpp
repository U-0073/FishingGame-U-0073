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
	ScoreData = DTWHOUCE.GetVec("score");
	if (ScoreData.Success) {
		vTex = RESOURCE_MNG.GetTexture("board.png");
		mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mMat.SetTrans(0.0f, 0.0f, 0.0f);
	}
	else {
		vTex = RESOURCE_MNG.GetTexture("escape.png");
		mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mMat.SetTrans(0.0f, 0.0f, 0.0f);
		mMat.SetScale(2.0f, 2.0f, 2.0f);
		vBackTex = RESOURCE_MNG.GetTexture("SeaBack001.png");
		mBackPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mMat.SetTrans(0.0f, 0.0f, 0.0f);
	}
}

void Result::Update()
{
	if (ScoreData.Success) {
		mPos = D3DXVECTOR3(1280.0f / 2, 720.0f / 3 * 2.3, 0.0f);
		D3DXMatrixTranslation(&mMat, mPos.x, mPos.y, mPos.z);
		mMat.SetTrans(mPos.x, mPos.y, mPos.z);
	}
	else {
		mPos = D3DXVECTOR3(1280.0f / 2, 720.0f /2, 0.0f);
		mMat.SetTrans(mPos.x, mPos.y, mPos.z);
		mBackPos = D3DXVECTOR3(1280.0f / 2, 720.0f /2, 0.0f);
		mBackMat.SetTrans(mBackPos.x, mBackPos.y, mBackPos.z);
	}
}

void Result::Draw2D()
{
	if (ScoreData.Success) {
		RECT rcBoard = { 0,0,1000,380 };
		SPRITE->SetTransform(&mMat);
		SPRITE->Draw(*vTex, &rcBoard, &D3DXVECTOR3(1000.0f / 2, 380.0f / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else {
		RECT rcBack = { 0,0,1280,720 };
		SPRITE->SetTransform(&mBackMat);
		SPRITE->Draw(*vBackTex, &rcBack, &D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	
		RECT rcEscape = { 0,0,336,200 };
		SPRITE->SetTransform(&mMat);
		SPRITE->Draw(*vTex, &rcEscape, &D3DXVECTOR3(336.0f / 2, 200.0f / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Result::Draw3D()
{
}

void Result::End()
{
	vTex = nullptr;
}

