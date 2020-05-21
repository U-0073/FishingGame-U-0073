#pragma once
#include"../System/FrameBase/GameObject.h"

class Port : GameObject
{
public:
	Port();
	~Port();
	
	void Init()override;
	void Update()override;
	void Draw3D()override;
	void End()override;
private:
	std::shared_ptr<KdModel> ShopModel = nullptr;
	KdMatrix ShopMat;
};