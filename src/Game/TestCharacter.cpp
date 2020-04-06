#include"../System/KdLibrary/KdLibrary.h"
#include"TestCharacter.h"

TestCharacter::TestCharacter()
{
}

TestCharacter::~TestCharacter()
{
}

void TestCharacter::Init(LPDIRECT3DDEVICE9 &lpD3DDevice)
{
	GameObject::Init(lpD3DDevice);
	m_pModel = RESOURCE_MNG.GetModel(lpD3DDevice,"./Resouce/3DModel/body.x");
}

void TestCharacter::Update()
{
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 10, -0), D3DXVECTOR3(0, 0, 0));
}

void TestCharacter::Draw3D(LPDIRECT3DDEVICE9 mpD3DDevice)
{
	KD3D.SetWorldMatrix(&m_world);

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}
