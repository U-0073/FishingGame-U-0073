#include"../System/KdLibrary/KdLibrary.h"
#include"Port.h"

Port::Port()
{
}

Port::~Port()
{
	m_pModel = nullptr;
}

void Port::Init()
{
	D3DXMatrixTranslation(&m_world, 0, -1.5, 0);
	m_pModel = RESOURCE_MNG.GetModel("Port");
	ShopMat.SetTrans(14, -0.6f, -42);

	ShopModel = RESOURCE_MNG.GetModel("Shop");

}

void Port::Update()
{
}

void Port::Draw3D()
{

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	KD3D.SetWorldMatrix(&m_world);
	m_pModel->Draw();


	KD3D.SetWorldMatrix(&ShopMat);
	ShopModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void Port::End()
{
	m_pModel = nullptr;
	ShopModel = nullptr;
}
