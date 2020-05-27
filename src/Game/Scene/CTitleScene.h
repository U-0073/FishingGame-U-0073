#pragma once
#include"../../System/FrameBase/CSceneBase.h"


class Skysphere;
class Fish;
class Title;
class Sea;

class CTitleScene : public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;

	int GetID()override { return TITLE; };

	void End()override;
private:
	std::shared_ptr<Skysphere>	Sky		= nullptr;
	std::shared_ptr<Fish>		Fishes	= nullptr;
	std::shared_ptr<Title>		title	= nullptr;
	std::shared_ptr<Sea>		sea		= nullptr;
	
	KdVec3 score;
	
	int Excellent;//�f�o�b�N
	int Miss;
	bool clear;

	D3DXVECTOR3 mPos;
	BOOL MoveFlg;

	std::shared_ptr<SoundBase> m_PSound = nullptr;
	std::shared_ptr<SoundBase> m_PSE = nullptr;

};
