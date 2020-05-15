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
	
	D3DXMATRIX ScaleMat;
	D3DXMatrixScaling(&ScaleMat, 1.5f, 1.5f, 1.5f);
	m_world = ScaleMat * m_world;

}

void Skysphere::Update(void)
{
	
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
