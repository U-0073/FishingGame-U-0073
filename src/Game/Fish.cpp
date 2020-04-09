#include"../System/KdLibrary/KdLibrary.h"
#include"Fish.h"

Fish::Fish()
{
}

Fish::~Fish()
{
}

void Fish::Init()
{
	D3DMATRIX ScaleMat;
	D3DXMatrixScaling(&ScaleMat, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&m_world, (rand() % 50) / 10, 0, (rand() % 5) / 10);
	int name = rand() % 3;
	switch (name)
	{
	case 0:
		m_Tag = "RedSnapper";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/RedSnapper.x");
		break;
	case 1:
		m_Tag = "Saury";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Saury.x");
		break;
	case 2:
		m_Tag = "Tuna";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Tuna.x");
		break;
	}
}

void Fish::Update()
{
	if (GetKey('Q') & 0x8000)
	{
		Init();
	}
}

void Fish::Draw2D()
{
}

void Fish::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
