#pragma once

#include"../System/FrameBase/GameObject.h"

#define path "Resouce/3DModel/"
class Fish;

class C_Fishing : GameObject {
public:
	C_Fishing();
	~C_Fishing();

	void Init()	override;
	void Start();
	void End();
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

	const void SetPlayerVec(const KdVec3& Vec) { PlayerVec = Vec; }
	const void SetCamAngY(const float& f) { CamAngY = f; }
	const void SetFishFlg(const bool& flg) { FishSceneFlg = flg; }
	const void SetBuoiFlg(const bool& flg) { BuoiFlg = flg; }
private:

	void FishingProc();

	std::shared_ptr<Fish> Fishes = nullptr;

	KdVec3 BuoiPos;
	KdVec3 PlayerVec;
	KdVec3 Len;

	KdMatrix ScileMat;
	KdMatrix TransMat;

	float BuoiPosY = -3.7f;
	float CamAngY;
	bool  FishSceneFlg = false;
	bool BuoiFlg = false;
	bool GetFish = false;
};