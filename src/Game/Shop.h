#pragma once
#include"../System/FrameBase/GameObject.h"



class Shop : GameObject
{
public:
	Shop();
	~Shop();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

private:

};

