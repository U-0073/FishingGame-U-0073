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
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/F-15.x");
}

void TestCharacter::Update()
{
}

void TestCharacter::Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
	KD3D.SetWorldMatrix(&m_world);

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}
