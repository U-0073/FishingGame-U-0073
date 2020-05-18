#include"../System/KdLibrary/KdLibrary.h"
#include "Seagull.h"

Seagull::Seagull()
{
}

Seagull::~Seagull()
{
}

void Seagull::Init()
{
	GameObject::Init();

	ScaleMat.CreateScale(0.1f, 0.1f, 0.1f);
	TransMat.CreateTrans(0.0f, 0.0f, 0.0f);
	m_world = ScaleMat * TransMat;
	m_pModel = RESOURCE_MNG.GetModel(SEagull);

}

void Seagull::Update()
{
}

void Seagull::Draw2D()
{
}

void Seagull::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Seagull::End()
{
	m_pModel = nullptr;
}
