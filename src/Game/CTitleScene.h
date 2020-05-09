#pragma once
#include"../System/FrameBase/CSceneBase.h"
#define path "Resource/Texture/"
#include"Title.h"
#include"Skysphere.h"
#include"Fish.h"
#include"Sea.h"

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
	

	D3DXVECTOR3 mPos;
	BOOL MoveFlg;

	std::shared_ptr<SoundBase> m_PSound = nullptr;

};