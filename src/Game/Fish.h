#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"

class Fish : GameObject
{
public:
	Fish();
	~Fish();
	void SetTagType(int No);
	
	void Init()override;

	inline void SetCenter(KdVec3 pos) {
		Center = pos;

	};
	const KdVec3& GetPos() {
		return m_world.GetPos();
	}
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

	void TitleUpdate();

	const void SetPlayerPos(const KdVec3& Vec) { PlayerPos = Vec; }
	const void SetCamAngY(const float& f) { CamAngY = f; }
	const void SetFishFlg(const bool& flg) { FishFlg = flg; }
	
	const D3DXVECTOR3& GetFishPos() { return FishPos; }

private:
	std::string m_Tag;//‰½‚Ì‹›‚©
	
	KdVec3 Center;

	KdVec3 PlayerPos;
	KdVec3 FishPos;
	KdVec3 FishLen;
	KdMatrix TransMat;
	KdMatrix ScaleMat;

	float Count = 0.0f;
	float CamAngY;
	bool  FishFlg;
};

class Fishes {
public:
	void Init();

	void Update();
	void Draw2D();
	void Draw3D();
	void End() {
		for (auto&& p : m_Fihes) {
			for (auto&& pp : p) {
				pp->End();
				

			}
			p.clear();
		}
		CenterPoss.clear();
	}

private:
	std::vector<std::vector<std::shared_ptr<Fish>>>m_Fihes;
	std::vector<KdVec3>CenterPoss;

};