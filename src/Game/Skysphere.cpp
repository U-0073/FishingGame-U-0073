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
	m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/SkySphere.x");
}

void Skysphere::Update(void)
{
	
}

void Skysphere::Draw3D()
{
	D3DXMATRIX ScaleMat;
	D3DXMatrixScaling(&ScaleMat, 1, 1, 1);
	//m_world = ScaleMat * m_world;
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}
