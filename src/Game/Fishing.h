#pragma once

#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"
class Fishes;

class C_Fishing : GameObject {
public:
	C_Fishing();
	~C_Fishing();

	void Init()	override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

	const void SetFishingFlg(const bool& flg) { FishingFlg = flg; }
	const void SetBuoyFlg(const bool& flg) { BuoyFlg = flg; }
private:

	void CameraProc();
	void FishingProc();



	std::shared_ptr<Fishes> m_Fishes = nullptr;

	KdVec3 BuoyPos;
	KdVec3 PlayerPos;
	KdVec3 Len;

	KdMatrix ScileMat;
	KdMatrix TransMat;

	float BuoyPosY = -3.7f;
	bool  FishingFlg = false;
	bool  BuoyFlg = false;
	bool  StopFlg = false;
	bool  HitFlg = false;

};