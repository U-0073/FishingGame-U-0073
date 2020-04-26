#include"../System/KdLibrary/KdLibrary.h"
#include"ShopObject.h"

CShopObject::CShopObject()
{
}

CShopObject::~CShopObject()
{
}

void CShopObject::Init()
{
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resource/3DModel/Shop.x");
}

void CShopObject::Update()
{
}

void CShopObject::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
