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
	const std::string& getTag() {
		return m_Tag;
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

	void TitleInit();
	void TitleUpdate();
	void ResultInit();


	
	const D3DXVECTOR3& GetFishPos() { return m_world.GetPos(); }

private:

	void MoveHorizontal();

	std::string m_Tag;//���̋���
	
	//�Q��̒��S���W
	KdVec3 Center;
	//�E�L�̈ʒu
	KdVec3 BuoyPos;

	KdVec3 FishPos;
	KdMatrix TransMat;
	KdMatrix ScaleMat;


	float Count = 0.0f;
	float AngY;
	bool  FishFlg;


	//���e�p
public:
	void ShadowInit();
	void ShadowUpdate();
	void ShadowDraw();

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9> ShadowTex = nullptr;
	KdVec3 ShadowPos;
	KdMatrix ShadowMat;
	VERTEX Shadow[4];
};

//�Q�ꂽ���̓����B��C���̏W����
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