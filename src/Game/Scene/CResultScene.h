#pragma once
#include"../../System/FrameBase/CSceneBase.h"

#include"../Skysphere.h"
#include"../Fish.h"
#include"../Sea.h"
#include"../Result.h"

class CGameProc;
class Skysphere;
class Fish;
class Sea;
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

private:
	D3DXVECTOR3 mPos;
	BOOL MoveFlg;

	std::shared_ptr<Skysphere>	Sky = nullptr;
	std::shared_ptr<Fish>		Fishes = nullptr;
	std::shared_ptr<Sea>		sea = nullptr;
	std::shared_ptr<Result>     result = nullptr;
	std::shared_ptr<SoundBase> m_pSound = nullptr;

};