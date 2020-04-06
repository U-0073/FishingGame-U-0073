#include"../System/KdLibrary/KdLibrary.h"
#include"TestCharacter.h"

TestCharacter::TestCharacter()
{
}

TestCharacter::~TestCharacter()
{
}

void TestCharacter::Init()
{
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/body.x");
}

void TestCharacter::Update()
{
}

void TestCharacter::Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
