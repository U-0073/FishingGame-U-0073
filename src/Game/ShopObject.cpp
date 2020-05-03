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
	m_pNormalRod1 = RESOURCE_MNG.GetModel("./Resource/3DModel/Tuna.x");
	//m_pNormalRod2 = RESOURCE_MNG.GetModel("./Resource/3DModel/Tuna.x");
	//m_pNormalRod3 = RESOURCE_MNG.GetModel("./Resource/3DModel/Tuna.x");
}

void ShopObject::Update()
{

}

void ShopObject::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	m_pNormalRod1->Draw();
	//m_pNormalRod2->Draw();
	//m_pNormalRod3->Draw();

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}
