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

	//std::shared_ptr<KdModel> m_pNormalRod[8] = nullptr;
	//std::shared_ptr<KdModel> m_pNormalRod2 = nullptr;
	//std::shared_ptr<KdModel> m_pNormalRod3 = nullptr;

	std::map<std::string, std::shared_ptr<KdModel>> Rod;
	

	int tPattern;
};