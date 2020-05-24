#pragma once
#include"../System/FrameBase/GameObject.h"

class Skysphere : GameObject
{
public:
	Skysphere();
	~Skysphere();

	void Init()override;
	void Update(void)override;
	void Draw3D()override;
	void End()override;

private:
	std::shared_ptr<KdModel> m_pModel2 = nullptr;
	D3DXVECTOR3 PlayerPos;
};