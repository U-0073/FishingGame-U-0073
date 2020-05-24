#include"../System/KdLibrary/KdLibrary.h"
#include"Skysphere.h"

Skysphere::Skysphere()
{
}

Skysphere::~Skysphere()
{
}

void Skysphere::Init()
{
	GameObject::Init();	
	m_pModel = RESOURCE_MNG.GetModel("SkySphere2");
	m_pModel2 = RESOURCE_MNG.GetModel("SeaSphere");
	
	m_world.SetScale(1.5, 1.5, 1.5);
}

void Skysphere::Update(void)
{
	m_world.SetTrans(DTWHOUCE.GetVec("Player"));
}

void Skysphere::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pModel->Draw();
	m_pModel2->Draw();
}

void Skysphere::End()
{
	m_pModel = nullptr;
	m_pModel2 = nullptr;
}
