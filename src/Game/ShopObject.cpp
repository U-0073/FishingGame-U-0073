#include"../System/KdLibrary/KdLibrary.h"
#include"ShopObject.h"

ShopObject::ShopObject()
{
}

ShopObject::~ShopObject()
{
	m_pModel = nullptr;
	m_pNormalRod1 = nullptr;
	m_pNormalRod2 = nullptr;
	m_pNormalRod3 = nullptr;
}

void ShopObject::Init()
{
	GameObject::Init();
	m_pNormalRod1 = RESOURCE_MNG.GetModel("./Resource/3DModel/FishingLod.x");
	//m_pNormalRod2 = RESOURCE_MNG.GetModel("./Resource/3DModel/FishingLod.x");
	//m_pNormalRod3 = RESOURCE_MNG.GetModel("./Resource/3DModel/FishingLod.x");

	D3DXMatrixTranslation(&m_world, 3, -3, 0);
}

void ShopObject::Update()
{
	static D3DXMATRIX m_rot;
	static float rot = 0;
	rot = 1.0f;
	D3DXMatrixRotationY(&m_rot, D3DXToRadian(rot));
	m_world = m_rot * m_world;
}

void ShopObject::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (tPattern == 0) {
		m_pNormalRod1->Draw();
		//m_pNormalRod2->Draw();
		//m_pNormalRod3->Draw();
	}

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void ShopObject::GetListChange(int tPat)
{
	tPattern = tPat;
}
