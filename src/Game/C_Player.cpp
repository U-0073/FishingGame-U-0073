#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"
#include "../System/FrameBase/CGameFrame.h"


#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Player::C_Player()
{
}

C_Player::~C_Player()
{
	End();
}

void C_Player::Init()
{
	PlayerPos = InitPos;
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/body.x");

	//�|�C���^�[�֌W
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//�Q�[����ʓ����W�˃p�\�R����ʓ����W
										//	�@�i�N���C�A���g���W�j�i�X�N���[�����W�j
	SetCursorPos(BasePt.x, BasePt.y);
	ShowCursor(FALSE);

	auto Json = std::make_shared<json11::Json>();
	Json = JSONS.LoadJson("Default/Test.json");

	int i = (*Json)["value1"].int_value();

	std::string tag = "Player";//VisualStudio�o�O�΍��string�͈�x�錾���Ă�������
	bool test1 = JSONS.checkValue(Json, "Tag", tag);


	bool test3 = JSONS.checkValue(Json, "value1", 111);
	bool test4 = JSONS.checkValue(Json, "value1", 333);

	bool test5 = JSONS.checkValue(Json, "value2", 2.2);
	bool test6 = JSONS.checkValue(Json, "value2", 3.3);

	//�܂��g���Ȃ�
	//JSONS.AddKeyValue(Json,"Value5", std::string("ABCD"));

	JSONS.SaveJson(Json, "Save/Test.json");








}
void C_Player::Begin()
{
}
void C_Player::End()
{
	m_pModel = nullptr;
}


void C_Player::Update()
{
	FlgProc();
	MoveProc();
	CameraProc();
}

void C_Player::FlgProc()
{
	//�}�E�X�ł̃J�����ړ���on off
	static bool	ClickStop = false;
	if (GetKey('E') & 0x8000)
	{
		if (!ClickStop)
		{
			ClickStop = true;

			if (FishFlg) {
				ShowCursor(TRUE);
				FishFlg = false;
				RestoreFlg = true;
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
}

void C_Player::MoveProc()
{
	static bool KeyCheck = false;
	bool	MoveFlg = false;

	if (!FishFlg) {
		if (GetKey('W') & 0x8000) {//�O��
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);
			PlayerPos += Vec * MoveSpeed;
		}
		if (GetKey('A') & 0x8000) {//��
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			PlayerPos += Vec * MoveSpeed;
		}
		if (GetKey('S') & 0x8000) {//����
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			PlayerPos += Vec * MoveSpeed;
		}
		if (GetKey('D') & 0x8000) {//�E
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			PlayerPos += Vec * MoveSpeed;
		}
	}

	TransMat.CreateTrans(PlayerPos);
	D3DXMatrixRotationY(&PlayerRot, D3DXToRadian(CamAngY));
	m_world = PlayerRot * TransMat;
}


void C_Player::CameraProc()
{
	if (!FishFlg && !RestoreFlg) {
		if (GetKey(VK_RIGHT) & 0x8000) {
			CamAngY += 2;
		}
		if (GetKey(VK_LEFT) & 0x8000) {
			CamAngY -= 2;
		}
		if (GetKey(VK_UP) & 0x8000) {
			CamAngX -= 2;
		}
		if (GetKey(VK_DOWN) & 0x8000) {
			CamAngX += 2;
		}
	}

	//�}�E�X�֌W�̌v�Z
	MouseUpdate();

	//�ނ��Ԉڍs���̃J�����̓���
	CameraSet();
}
void C_Player::MouseUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	//�ނ胂�[�h����Ȃ��Ƃ��Ƀ}�E�X�ŃJ�����̉�]���ł���悤�Ɉړ�������
	if (!FishFlg && !RestoreFlg)
	{
		long Move = (Pt.x - BasePt.x);
		if ((Move >= 3) || (Move <= -3))
		{
			CamAngY += (Pt.x - BasePt.x) / 4.0f;
			CamAngX += (Pt.y - BasePt.y) / 4.0f;
		}
	}

	//�J�����̉�]�ő�l�𐧌�
	if (CamAngY < -180)	CamAngY = 180;
	if (CamAngY > 180)	CamAngY = -180;

	if (CamAngX < -80.0f) CamAngX = -80.0f;
	if (CamAngX > 20.0f && !RestoreFlg) CamAngX = 20.0f;

	if (!FishFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static KdVec3		CamPos;
	static KdVec3		CamLook;
	static float		_CamAngX;
	static bool			flg1 = false;
	static bool			flg2 = false;
	static bool			StopFlg = false;//�ނ胂�[�h�Ɉڍs�������̊Ԃ��������������p

	//�J�����̈ړ����I������Ƃ��ɕ����������悤�ɂ������
	if (flg1 && flg2) { BuoiFlg = true; }
	else { BuoiFlg = false; }

	//�ނ胂�[�h����Ȃ��Ƃ�
	if (!FishFlg) {
		StopFlg = false;
		//�ނ胂�[�h���������ꂽ�Ƃ��A�J�����̉�]�����Ƃɖ߂�
		if (FishScene_CamAngX > 0) {
			FishScene_CamAngX -= 0.6f;
			if (RestoreFlg) {
				CamAngX -= 0.6f;
				flg1 = false;
			}
		}
		else FishScene_CamAngX = 0;

		//�������������ꂽ�Ƃ��ɃJ�����̈ʒu��߂�
		if (FishScene_CamPos.Length() > PlayerPos.y + FishScene_LenMin) {
			KdMatrix		CamRot;
			KdVec3			TmpVec;

			CamRot.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Z, &CamRot);
			FishScene_CamPos -= TmpVec * 0.05f;
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Y, &CamRot);
			FishScene_CamPos -= TmpVec * 0.1f;
		}
		else {
			FishScene_CamPos = InitCamPos;
			flg2 = false;
		}

		if (FishScene_CamPos.Length() == FishScene_LenMin && FishScene_CamAngX == 0) {
			RestoreFlg = false;
		}


		KdMatrix			CamRot;
		D3DXVECTOR3			Vec;

		CamRot.CreateRotation(D3DXToRadian(CamAngX), D3DXToRadian(CamAngY), 0);
		D3DXVec3TransformCoord(&Vec, &CoordVec.Z, &CamRot);

		CamLook = Vec;
		CamPos = PlayerPos + FishScene_CamPos;
	}

	//�ނ胂�[�h�̎�
	if (FishFlg) {
		if (!StopFlg) {
			FishScene_CamAngX = CamAngX;
			StopFlg = true;
		}
		//�J�����̃A���O����ύX����v���O����
		if (FishScene_CamAngX < CamAngX_MaxLimit)FishScene_CamAngX += 0.4f;
		else {
			FishScene_CamAngX = CamAngX_MaxLimit;
			flg1 = true;
		}

		//�J�����̈ʒu��ς���v���O����
		if (FishScene_CamPos.Length() < FishScene_LenMax + PlayerPos.y) {
			KdMatrix CamRot;
			KdVec3 TmpVec;

			CamRot.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Z, &CamRot);
			FishScene_CamPos += TmpVec * 0.025f;
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Y, &CamRot);
			FishScene_CamPos += TmpVec * 0.05f;
		}
		else {
			flg2 = true;
		}

		KdMatrix			CamRot;
		D3DXVECTOR3			Vec;

		CamRot.CreateRotation(D3DXToRadian(FishScene_CamAngX), D3DXToRadian(CamAngY), 0);
		D3DXVec3TransformCoord(&Vec, &CoordVec.Z, &CamRot);
		CamLook = Vec;

		CamPos = PlayerPos + FishScene_CamPos;
		CamAngX = FishScene_CamAngX;
	}


	CAMERA.SetCameraVec(CamPos, CamLook);
}


void C_Player::Draw3D() {
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	Draw3DWall();
}
void C_Player::Draw2D()
{
	char Text[100];
	RECT rcText = { 10,30 * 1,0,0 };
	sprintf_s(Text, sizeof(Text), "FishSceneLength %f", FishScene_CamPos.Length());
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText1 = { 10,30 * 7,0,0 };
	sprintf_s(Text, sizeof(Text), "FishSceneCamAng x %f CamAng x %f  y%f", FishScene_CamAngX, CamAngX, CamAngY);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText1, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText2 = { 10,30 * 2,0,0 };
	sprintf_s(Text, sizeof(Text), "PlayerPos  x %f  y%f z %f ", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText2, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText3 = { 10,30 * 3,0,0 };
	if (!RestoreFlg)KD3D.GetFont()->DrawText(NULL, "RestoreFlg=false", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else KD3D.GetFont()->DrawText(NULL, "RestoreFlg=true", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText4 = { 10,30 * 4,0,0 };
	if (!FishFlg)KD3D.GetFont()->DrawText(NULL, "FishFlg=false", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else KD3D.GetFont()->DrawText(NULL, "FishFlg=true", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText5 = { 10,30 * 5,0,0 };
	if (!BuoiFlg)KD3D.GetFont()->DrawText(NULL, "BuoiFlg=false", -1, &rcText5, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else KD3D.GetFont()->DrawText(NULL, "BuoiFlg=true", -1, &rcText5, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText6 = { 10,30 * 6,0,0 };
	sprintf_s(Text, sizeof(Text), "FishingScene_CamPos  x %f  y%f z %f ", FishScene_CamPos.x, FishScene_CamPos.y, FishScene_CamPos.z);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText6, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}





