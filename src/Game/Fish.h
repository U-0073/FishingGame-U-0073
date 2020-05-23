#pragma once
#include"../System/FrameBase/GameObject.h"

#define path "Resource/3DModel/"

class Fish : GameObject
{
public:
	Fish();
	~Fish();
	void SetTagType(int No);
	void SetTagType(std::string name) { m_Tag = name; }
	
	void Init()override;
	const std::string& getTag() {
		return m_Tag;
	}
	void setBuoy(const KdVec3 Pos) {

		BuoyPos = Pos;
	}
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
	void ResultUpdate();


	const void SetPlayerPos(const KdVec3& Vec) { PlayerPos = Vec; }
	const void SetFishingFlg(const bool& flg) { FishFlg = flg; }
	
	const D3DXVECTOR3& GetFishPos() { return m_world.GetPos(); }

private:
	std::string m_Tag;//何の魚か
	
	//群れの中心座標
	KdVec3 Center;
	//ウキの位置
	KdVec3 BuoyPos;

	KdVec3 PlayerPos;
	KdVec3 FishPos;
	KdMatrix TransMat;
	KdMatrix ScaleMat;


	float Count = 0.0f;
	float AngY;
	bool  FishFlg;
};

//群れた時の動き。一匹ずつの集合体
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
		CenterPos.clear();
	}

private:
	std::vector<std::vector<std::shared_ptr<Fish>>>m_Fihes;
	std::vector<KdVec3>CenterPos;

};