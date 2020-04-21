#pragma once
#include"../System/FrameBase/GameObject.h"

class CShopObject : GameObject
{
public:
	CShopObject();
	~CShopObject();

	void Init()override;
	void Update()override;
	void Draw3D()override;
private:

};