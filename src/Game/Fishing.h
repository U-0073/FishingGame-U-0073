#pragma once

#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"
class Fish;

class C_Fishing : GameObject {
public:
	C_Fishing();
	~C_Fishing();

	void Init()	override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

	const void SetPlayerPos(const KdVec3& Vec) { PlayerPos = Vec; }
	const void SetCamAngY(const float& f) { CamAngY = f; }
	const void SetFishFlg(const bool& flg) { FishSceneFlg = flg; }
	const void SetBuoiFlg(const bool& flg) { BuoiFlg = flg; }
private:

	void CameraProc();
	void FishingProc();

	std::shared_ptr<Fish> Fishes = nullptr;

	KdVec3 BuoiPos;
	KdVec3 PlayerPos;
	KdVec3 Len;

	KdMatrix ScileMat;
	KdMatrix TransMat;

	float BuoiPosY = -3.7f;
	float CamAngY;
	bool  FishSceneFlg = false;
	bool BuoiFlg = false;
	bool GetFish = false;
};