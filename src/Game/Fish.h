#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resouce/3DModel/"

class Fish : GameObject
{
public:
	void Init()override;
	void Update()override;
	void Draw3D()override;

private:
	std::string m_Tag;//���̋���

};