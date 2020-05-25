#pragma once
#include"../../System/FrameBase/CSceneBase.h"


class CGameProc;
class Skysphere;
class Fish;
class Result;


class CResultScene : public CSceneBase
{
public:
	CResultScene();
	~CResultScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return RESULT; };
	void End()override;

	//結果計算関数(サイズや売値など)
	void CalcData();
private:
	D3DXVECTOR3 mPos;

	std::shared_ptr<LPDIRECT3DTEXTURE9> NameTex = nullptr;
	KdMatrix mNameMat;
	std::shared_ptr<LPDIRECT3DTEXTURE9>NumberTex = nullptr;
	KdMatrix mNumberMat;
	KdMatrix mTransMat;
	KdMatrix mSizeScaleMat;
	std::shared_ptr<LPDIRECT3DTEXTURE9>CoinTex = nullptr;
	KdMatrix mCoinMat;
	std::shared_ptr<Skysphere>	Sky = nullptr;
	std::shared_ptr<Fish>		fish = nullptr;
	std::shared_ptr<Result>     result = nullptr;
	std::shared_ptr<SoundBase> m_pSound = nullptr;
	std::shared_ptr<SoundBase> SellSound = nullptr;

	KdVec3 ScoreData;
	float num[10];
	float Price = 0;
	float Size = 0;
};

#define Excellent x
#define Miss	  y
#define	Success	  z
