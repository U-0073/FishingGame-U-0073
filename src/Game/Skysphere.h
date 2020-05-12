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
	const void SetPos(const KdVec3& Pos) {
		m_world._41 = Pos.x, m_world._42 = Pos.y, m_world._43 = Pos.z;
	}
	void End()override;

private:
	std::shared_ptr<KdModel> m_pModel2 = nullptr;

};