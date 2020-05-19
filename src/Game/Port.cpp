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
	m_pModel = RESOURCE_MNG.GetModel("Port2");

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

void Port::End()
{
	
}
