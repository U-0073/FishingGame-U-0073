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
	void SetPos(KdVec3* Pos) {
		m_world._41 = Pos->x, m_world._42 = Pos->y, m_world._43 = Pos->z;
	}
};