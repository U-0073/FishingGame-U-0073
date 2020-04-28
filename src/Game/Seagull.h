#pragma once

#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"

class Seagull : GameObject
{
public:

	Seagull();
	~Seagull();
	void Init();
	void Update();
	void Draw2D();
	void Draw3D();

private:
	

};