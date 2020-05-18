#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"

class Seagull : GameObject
{
public:
	Seagull();
	~Seagull();
	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

private:
	std::string SEagull;

	KdVec3 SeagullPos;
	KdVec3 SeagullLen;
	KdMatrix TransMat;
	KdMatrix ScaleMat;
};