#pragma once
#include"../System/FrameBase/GameObject.h"

class GameObject;

class Sea :GameObject
{
public:
	Sea();
	~Sea();

	void Init()override {};
	void Update()override;
	void Draw2D()override {};
	void Draw3D()override;

private:
	DWORD verNum;
};