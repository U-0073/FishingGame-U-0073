#include"../System/KdLibrary/KdLibrary.h"
#include"TestCharacter.h"

TestCharacter::TestCharacter()
{
}

TestCharacter::~TestCharacter()
{
	m_pModel = nullptr;
}

void TestCharacter::Init()
{
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("body");
}

void TestCharacter::Update()
{
}

void TestCharacter::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
