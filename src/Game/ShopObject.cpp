#include"../System/KdLibrary/KdLibrary.h"
#include"ShopObject.h"

ShopObject::ShopObject()
{
}

ShopObject::~ShopObject()
{
}

void ShopObject::Init()
{
	GameObject::Init();
	m_pNormalRod1 = RESOURCE_MNG.GetModel("WoodRod");
	//m_pNormalRod2 = RESOURCE_MNG.GetModel("./Resource/3DModel/FishingLod.x");
	//m_pNormalRod3 = RESOURCE_MNG.GetModel("./Resource/3DModel/FishingLod.x");
	//ƒJƒƒ‰‚ÌÝ’è
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1));
	D3DXMatrixTranslation(&m_world, 0, 0, 0);

	m_world.RotateYLocal(D3DXToRadian(90));
	m_world.RotateXLocal(D3DXToRadian(-45));
	m_world.MoveWorld(2.0f, 0.0f, 7.0f);
}

void ShopObject::Update()
{
	//m_world.RotateYWorld(D3DXToRadian(1));
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

void ShopObject::End()
{
	m_pModel = nullptr;
	m_pNormalRod1 = nullptr;
	m_pNormalRod2 = nullptr;
	m_pNormalRod3 = nullptr;
}

void ShopObject::GetListChange(int tPat)
{
	tPattern = tPat;
}
