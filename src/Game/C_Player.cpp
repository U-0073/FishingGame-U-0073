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

	// フォント作成
	D3DXCreateFont(KD3D.GetDev(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &lpFont);


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
	lpFont->Release();
	m_pModel = nullptr;
}


void C_Player::Update()
{
	CameraProc();
	MoveProc();

	CmeraSet();
}
void C_Player::MoveProc()
{
	static bool KeyCheck = false;
	bool	MoveFlg = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
		D3DXVECTOR3	Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		PlayerVec += Vec * MoveSpeed;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
		D3DXVECTOR3	Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(-1, 0, 0), &RotMat);
		PlayerVec += Vec * MoveSpeed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
		D3DXVECTOR3	Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, -1), &RotMat);
		PlayerVec += Vec * MoveSpeed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
		D3DXVECTOR3	Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(1, 0, 0), &RotMat);
		PlayerVec += Vec * MoveSpeed;
	}


	//カメラの向きと連動した移動
	/*
	D3DXVECTOR3		moveVec(0, 0, 0);
	D3DXVECTOR3		TmpVec(0, 0, 0);

	if (GetAsyncKeyState('W') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, 1), &PlayerRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(-1, 0, 0), &PlayerRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, -1), &PlayerRot);
		moveVec += TmpVec;
		MoveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(1, 0, 0), &PlayerRot);
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
	*/
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
	RECT rcText = { 10,60 * 0,0,0 };
	char Text[100];
	sprintf_s(Text, sizeof(Text), "Playerの座標 \n %f %f %f", PlayerVec.x, PlayerVec.y, PlayerVec.z);
	lpFont->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText2 = { 10,60 * 1,0,0 };
	sprintf_s(Text, sizeof(Text), "CameraAngle  \n x=%f  y=%f ", CamAngX, CamAngY);
	lpFont->DrawText(NULL, Text, -1, &rcText2, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText3 = { 10,60 * 2,0,0 };
	sprintf_s(Text, sizeof(Text), "CamLook      \n x=%f  y=%f z=%f ", CamLook.x, CamLook.y, CamLook.z);
	lpFont->DrawText(NULL, Text, -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}


void C_Player::CameraProc()
{
	//マウスでのカメラ移動のon off
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

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		CamAngY += 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		CamAngY -= 1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		CamAngX += 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		CamAngX -= 1;
	}


	if (CamAngY > 180)CamAngY = -180;
	if (CamAngY < -180)CamAngY = 180;

	//マウス関係の計算
	PointUpdate();
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
void C_Player::CmeraSet()
{
	KdMatrix			CamRot;		//カメラの向いてる方向だけを管理する行列
	CamRot.CreateRotation(D3DXToRadian(CamAngX), D3DXToRadian(CamAngY), 0);

	D3DXVECTOR3 Vec;
	D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &CamRot);
	CamLook = Vec;

	CAMERA.SetCameraPos(PlayerVec, CamLook);
}


