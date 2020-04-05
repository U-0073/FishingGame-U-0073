#pragma once
#include"../System/FrameBase/CSceneBase.h"

class TestCharacter;

class CGameScene : public CSceneBase
{
public:
	CGameScene(LPDIRECT3DDEVICE9 lpD3DDevice);
	~CGameScene();

	void Update()override;
	void Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice)override;
	void Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)override;

private:
	std::shared_ptr<TestCharacter> test = nullptr;
};