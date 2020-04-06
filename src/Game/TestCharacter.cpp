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
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 10, -0), D3DXVECTOR3(0, 0, 0));
}

void TestCharacter::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
