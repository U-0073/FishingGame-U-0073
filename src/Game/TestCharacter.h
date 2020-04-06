#pragma once
#include"../System/FrameBase/GameObject.h"

class TestCharacter : GameObject
{
public:
	TestCharacter();
	~TestCharacter();

	void Init(LPDIRECT3DDEVICE9& lpD3DDevice)override;
	void Update()override;
	void Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)override;
private:

};