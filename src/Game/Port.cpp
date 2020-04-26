#include"../System/KdLibrary/KdLibrary.h"
#include"Port.h"

Port::Port()
{
}

Port::~Port()
{
}

void Port::Init()
{
	D3DXMatrixTranslation(&m_world, 0, -1.5, 0);
m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Port2.x");

}

void Port::Update()
{
}

void Port::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
