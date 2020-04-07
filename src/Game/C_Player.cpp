#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"


#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Player::C_Player()
{
	Start();
}

C_Player::~C_Player()
{
	End();
}

void C_Player::Init()
{
	PlayerVec.Set(0.0f, 0.0f, 0.0f);
}
void C_Player::Start()
{
	PlayerVec = StartVec;
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/body.x");


	//ポインター関係
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	//	ClientToScreen(hwnd, &BasePt);		//ゲーム画面内座標⇒パソコン画面内座標
											//	　（クライアント座標）（スクリーン座標）
	//	SetCursorPos(BasePt.x, BasePt.y);
	//	ShowCursor(FALSE);
}
void C_Player::End()
{

	m_pModel = nullptr;
}


void C_Player::Update()
{
	PlayerVec = KdVec3(m_world._41, m_world._42, m_world._43);

	//これはマウスでの視点移動をやめるか続けるかの処理 
	//※まだ動かすことができないためコメントアウト

	/*
	static bool	ClickStop = false;
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (!ClickStop)
		{
			CursorFlg = !CursorFlg;
			ClickStop = true;

			if (CursorFlg)	ShowCursor(TRUE);
			else
			{
				ShowCursor(FALSE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
		}
	}
	else ClickStop = false;
	*/

	MoveProc();

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 10, -10), D3DXVECTOR3(0, 0, 0));
	//CAMERA.SetCameraPos(D3DXVECTOR3(PlayerVec.x, PlayerVec.y + 10.0f, PlayerVec.z), D3DXVECTOR3(PlayerVec.x, PlayerVec.y, PlayerVec.z + 1));

}

void C_Player::Draw3D() {
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}
void C_Player::Draw2D()
{
}


void C_Player::CameraProc()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		CamAngY += 2;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		CamAngY -= 2;
	}

	if (CamAngY > 180)CamAngY = -180;
	if (CamAngY < -180)CamAngY = 180;

	PointUpdate();

}
void C_Player::MoveProc()
{
	static bool KeyCheck = false;
	bool	MoveFlg = false;
	D3DXVECTOR3		moveVec(0, 0, 0);
	D3DXVECTOR3		TmpVec(0, 0, 0);

	//カメラの向きと連動した移動
	if (GetAsyncKeyState('W') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, 1), &CamRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(-1, 0, 0), &CamRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, -1), &CamRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(1, 0, 0), &CamRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}


	if (MoveFlg)
	{
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= MoveSpeed;
		KdMatrix		tmpMat;

		tmpMat.CreateTrans(moveVec);
		TransMat = tmpMat * TransMat;
	}

	D3DXMatrixRotationY(&CamRot, D3DXToRadian(CamAngY));
	m_world = CamRot * TransMat;
}

void C_Player::PointUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	if (!CursorFlg)
	{
		long Move = (Pt.x - BasePt.x);
		if ((Move >= 3) || (Move <= -3))
		{
			CamAngY += (Pt.x - BasePt.x) / 4.0f;
			CamAngX += (Pt.y - BasePt.y) / 4.0f;
		}
	}

	if (CamAngX > 80.0f) CamAngX = 80;
	if (CamAngX < -80.0f) CamAngX = -80;


	if (!CursorFlg) SetCursorPos(BasePt.x, BasePt.y);

}


