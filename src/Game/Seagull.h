#pragma once
#include"../System/FrameBase/GameObject.h"

class GameObject;

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

	std::shared_ptr<SoundBase> testsound = nullptr;

	KdVec3 SeagullPos;
	KdVec3 SeagullLen;
	KdMatrix TransMat;
	KdMatrix RotMat;
};