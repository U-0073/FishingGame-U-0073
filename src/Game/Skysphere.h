#pragma once
#include"../System/FrameBase/GameObject.h"

class Skysphere : GameObject
{
public:
	Skysphere();
	~Skysphere();

	void Init()override;
	void Update(void)override;
	void Draw3D()override;
};