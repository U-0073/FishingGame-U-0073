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

	void Get2D(int, int);

private:


	std::map<std::string, std::shared_ptr<KdModel>> Rod;
	std::map<std::string, std::shared_ptr<KdModel>> Reel;

	KdMatrix m_reel, m_reelScal, m_reelRot;

	int tPattern,Cur;
};