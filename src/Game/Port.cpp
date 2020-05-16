#include"../System/KdLibrary/KdLibrary.h"
#include"Port.h"

Port::Port()
{
}

Port::~Port()
{
	m_pModel = nullptr;
	testsound = nullptr;
}

void Port::Init()
{
	D3DXMatrixTranslation(&m_world, 0, -1.5, 0);
	m_pModel = RESOURCE_MNG.GetModel("Port2");

	testsound = RESOURCE_MNG.GetSound("umineko");
	testsound->LDS3B8->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	testsound->LDS3B8->SetPosition(0, 30, 0, DS3D_IMMEDIATE);
	testsound->Playsound("umineko", true, true);
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
	testsound->LDSB8->Stop();
}
