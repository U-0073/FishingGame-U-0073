#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"

class Seagull
{
public:
	Seagull();
	~Seagull();
	void Init();
	void Update();
	void Draw2D();
	void Draw3D();
	void End();

private:

	KdVec3 SeagullPos;
	KdVec3 SeagullLen;
	KdMatrix TransMat;
	KdMatrix ScaleMat;
};