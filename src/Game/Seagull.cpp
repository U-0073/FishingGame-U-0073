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

	m_pModel = RESOURCE_MNG.GetModel("Seagull");
	int r;

	srand(time(0));
	rand();
	r = rand();
	SeagullPos.x = r % 300 - 150;
	SeagullPos.y = r % 30 + 80;
	SeagullPos.z = r % 300 - 150;

	TransMat.CreateTrans(SeagullPos);
	m_world = RotMat * TransMat;

	testsound = RESOURCE_MNG.GetSound("umineko");
	testsound->LDS3B8->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	testsound->LDS3B8->SetPosition(SeagullPos.x, SeagullPos.y, SeagullPos.z, DS3D_IMMEDIATE);
	testsound->Playsound("umineko", true, true);
}

void Seagull::Update()
{
	
}

void Seagull::Draw2D()
{
	SPRITE->End();
	RECT rcText = { 10,0,0,0 };
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
	testsound->LDSB8->Stop();
	testsound = nullptr;

}
