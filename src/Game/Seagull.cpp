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
	m_pModel = RESOURCE_MNG.GetModel("Resource/3DModel/Seagull.x");
}

void Seagull::Update()
{
	SeagullLen = KdVec3(SeagullPos.x, SeagullPos.y+50, SeagullPos.z);
	KdVec3 m, n;

	float len = m.LengthToTarget(n);

}

void Seagull::Draw2D()
{
	SPRITE->End();
	RECT rcText = { 10,30 * 0,0,0 };
	char Text[10];
	sprintf_s(Text, sizeof(Text), "SeagullPos x %f y %f z %f", SeagullPos.x, SeagullPos.y, SeagullPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
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
