#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"
#include "../System/FrameBase/CGameFrame.h"


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
	PlayerVec.Set(0.0f, 1.0f, 0.0f);
}
void C_Player::Start()
{
	PlayerVec = StartVec;
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/body.x");



	//ポインター関係
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//ゲーム画面内座標⇒パソコン画面内座標
										//	　（クライアント座標）（スクリーン座標）
	SetCursorPos(BasePt.x, BasePt.y);
	ShowCursor(FALSE);
}
void C_Player::End()
{
	m_pModel = nullptr;
}


void C_Player::Update()
{
	CameraProc();
	MoveProc();

	CameraSet();
}
void C_Player::MoveProc()
{
	static bool KeyCheck = false;
	bool	MoveFlg = false;

	if (!FishFlg) {
		if (GetKey('W') & 0x8000) {
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
			PlayerVec += Vec * MoveSpeed;
		}
		if (GetKey('A') & 0x8000) {
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(-1, 0, 0), &RotMat);
			PlayerVec += Vec * MoveSpeed;
		}
		if (GetKey('S') & 0x8000) {
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, -1), &RotMat);
			PlayerVec += Vec * MoveSpeed;
		}
		if (GetKey('D') & 0x8000) {
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(1, 0, 0), &RotMat);
			PlayerVec += Vec * MoveSpeed;
		}
	}


	TransMat.CreateTrans(PlayerVec);

	D3DXMatrixRotationY(&PlayerRot, D3DXToRadian(CamAngY));
	m_world = PlayerRot * TransMat;


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
	//マウスでのカメラ移動のon off
	static bool	ClickStop = false;
	if (GetKey('E') & 0x8000)
	{
		if (!ClickStop)
		{
			ClickStop = true;

			if (FishFlg) {
				ShowCursor(TRUE);
				FishFlg = false;
				CntFlg = true;
			}
			else
			{
				FishFlg = true;
				ShowCursor(FALSE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
		}
	}
	else ClickStop = false;

	if (!FishFlg && !CntFlg) {
		if (GetKey(VK_RIGHT) & 0x8000) {
			CamAngY += 1;
		}
		if (GetKey(VK_LEFT) & 0x8000) {
			CamAngY -= 1;
		}
		if (GetKey(VK_UP) & 0x8000) {
			CamAngX -= 1;
		}
		if (GetKey(VK_DOWN) & 0x8000) {
			CamAngX += 1;
		}
		if (GetKey('Q') & 0x8000) {
			CamAngY -= 1;
		}
		if (GetKey('R') & 0x8000) {
			CamAngY += 1;
		}
	}


	if (CamAngY > 180)CamAngY = -180;
	if (CamAngY < -180)CamAngY = 180;

	//マウス関係の計算
	PointUpdate();
}
void C_Player::PointUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	if (!FishFlg && !CntFlg)
	{
		long Move = (Pt.x - BasePt.x);
		if ((Move >= 3) || (Move <= -3))
		{
			CamAngY += (Pt.x - BasePt.x) / 4.0f;
			CamAngX += (Pt.y - BasePt.y) / 4.0f;
		}
	}

	if (CamAngX < -80.0f) CamAngX = -80.0f;
	if (CamAngX > 10.0f && !CntFlg) CamAngX = 10.0f;

	if (!FishFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static KdVec3 CamPos;
	static KdVec3 _CamPos;
	static KdVec3 _CamLook;


	if (!FishFlg) {
		if (FishScene_CamAngX > 0) {
			FishScene_CamAngX--;
			if (CntFlg) {
				CamAngX-=0.5f;
			}
		}
		if (FishScene_CamPos.Length() > PlayerVec.y) {
			KdMatrix CamRot;
			CamRot.CreateRotationY(D3DXToRadian(CamAngY));
			KdVec3 TmpVec;
			D3DXVec3TransformCoord(&TmpVec, &D3DXVECTOR3(0.0f, 1.0f, 1.0f), &CamRot);

			FishScene_CamPos -= TmpVec * 0.1f;
		}
		else FishScene_CamPos.z = 0;
		if (FishScene_CamAngX == 0 && FishScene_CamPos.z == 0)CntFlg = false;


		KdMatrix			CamRot;		//カメラの向いてる方向だけを管理する行列
		CamRot.CreateRotation(D3DXToRadian(CamAngX), D3DXToRadian(CamAngY), 0);

		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &CamRot);
		CamLook = Vec;

		CamPos = PlayerVec + FishScene_CamPos;

		FishScene_CamAngX = CamAngX;
	}

	if (FishFlg) {
		if (FishScene_CamAngX < 50)FishScene_CamAngX+=0.5f;
		else FishScene_CamAngX = 50;

		if (FishScene_CamPos.Length() < 12.0f+ PlayerVec.y) {
			KdMatrix CamRot;
			CamRot.CreateRotationY(D3DXToRadian(CamAngY));
			KdVec3 TmpVec;
			D3DXVec3TransformCoord(&TmpVec, &D3DXVECTOR3(0.0f, 1.0f, 1.0f), &CamRot);

			FishScene_CamPos += TmpVec * 0.1f;
		}


		KdMatrix			CamRot;
		CamRot.CreateRotation(D3DXToRadian(FishScene_CamAngX), D3DXToRadian(CamAngY), 0);

		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &CamRot);
		CamLook = Vec;

		CamPos = PlayerVec + FishScene_CamPos;
		CamAngX = FishScene_CamAngX;
	}
	CAMERA.SetCameraPos(CamPos, CamLook);
}


