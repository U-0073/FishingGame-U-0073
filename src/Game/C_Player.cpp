#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"

C_Player::C_Player()
{
	Start();
}

C_Player::~C_Player()
{
	End();
}


void C_Player::Update()
{
	PlayerVec = KdVec3(m_world._41, m_world._42, m_world._43);


	static bool KeyCheck=false;

	if (GetAsyncKeyState('W') & 0x8000) {
		m_world.MoveWorld(0.0f, 0.0f, 0.1f);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_world.MoveWorld(-0.1f, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_world.MoveWorld(0.0f, 0.0f, -0.1f);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_world.MoveWorld(0.1f, 0.0f, 0.0f);
	}

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 10, -0), D3DXVECTOR3(0, 0, 0));

}

void C_Player::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void C_Player::Draw2D()
{
}


void C_Player::Init()
{
	PlayerVec.Set(0.0f, 0.0f, 0.0f);
}
void C_Player::Start()
{
	PlayerVec= StartVec;
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/body.x");
}
void C_Player::End()
{
	
	m_pModel = nullptr;
}
