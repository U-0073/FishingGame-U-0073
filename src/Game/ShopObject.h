#pragma once
#include"../System/FrameBase/GameObject.h"

class ShopObject : GameObject
{
public:
	ShopObject();
	~ShopObject();

	void Init()override;
	void Update()override;
	void Draw3D()override;
	void End()override;

	void GetListChange(int);

private:

	std::shared_ptr<KdModel> m_pNormalRod1 = nullptr;
	std::shared_ptr<KdModel> m_pNormalRod2 = nullptr;
	std::shared_ptr<KdModel> m_pNormalRod3 = nullptr;

	int tPattern;
};