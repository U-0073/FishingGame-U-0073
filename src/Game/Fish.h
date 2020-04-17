#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resouce/3DModel/"

class Fish : GameObject
{
public:
	Fish();
	~Fish();
	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

	void TitleUpdate();

	const void SetPlayerPos(const KdVec3& Vec) { PlayerPos = Vec; }
	const void SetCamAngY(const float& f) { CamAngY = f; }
	const void SetFishFlg(const bool& flg) { FishFlg = flg; }
	
	const D3DXVECTOR3& GetFishPos() { return FishPos; }

private:
	std::string m_Tag;//‰½‚Ì‹›‚©
	
	KdVec3 PlayerPos;
	KdVec3 FishPos;
	KdVec3 FishLen;
	KdMatrix TransMat;
	KdMatrix ScaleMat;

	float Count = 0.0f;
	float CamAngY;
	bool  FishFlg;
};