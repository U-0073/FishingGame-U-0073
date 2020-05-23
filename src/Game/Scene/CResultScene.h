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
	void SetTagType(std::string Name);
	int GetID()override { return RESULT; };
	void End()override;
	std::string GetData()override { return ""; };
	void SetData(std::string data);
private:
	D3DXVECTOR3 mPos;
	BOOL MoveFlg;

	std::shared_ptr<LPDIRECT3DTEXTURE9> NameTex = nullptr;
	KdMatrix mNameMat;

	std::shared_ptr<Skysphere>	Sky = nullptr;
	std::shared_ptr<Fish>		fish = nullptr;
	std::shared_ptr<Result>     result = nullptr;
	std::shared_ptr<SoundBase> m_pSound = nullptr;

};