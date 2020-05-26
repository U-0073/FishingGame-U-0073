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
}

void C_Player::Init()
{
	PlayerPos = { 0,0,0 };
	CAMERA.SetCameraVec(InitCamPos, KdVec3(0, 0, 1));
	CollisionMat.SetTrans(0.0f, -1.5f, 0.0f);
	ShopMat.SetTrans(14, -0.6f, -42);

	CollisionModel = RESOURCE_MNG.GetModel("PortWall_CollisionTest2");
	m_pModel = RESOURCE_MNG.GetModel("Portfloer_Collision");
	ShopModel = RESOURCE_MNG.GetModel("Shop");




	//�|�C���^�[�֌W
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//�Q�[����ʓ����W�˃p�\�R����ʓ����W
										//	�@�i�N���C�A���g���W�j�i�X�N���[�����W�j
	SetCursorPos(BasePt.x, BasePt.y);
	ShowCursor(FALSE);
	/*
		//�\�\�\�\�\�\�\�\�\�\�\�\�\�ȉ�Json�g�p��\�\�\�\�\�\�\�\�\�\�\�\//
		auto Json = std::make_shared<json11::Json>();
		Json = JSONS.LoadJson("Default/Test.json");//�ǂݍ���
		std::string tag = "Player";//VisualStudio�o�O�΍��string�͈�x�錾���Ă�������

	bool test1 = JSONS.checkValue(Json, "Tag", tag);//�������r
	test1 = JSONS.checkValue(Json, "Tag", 111);//�����Ɣ�r
	//�܂��g���Ȃ�
	JSONS.AddKeyValue(Json, "Value5", std::string("ABCD"));//�v�f�̕ύX�A�ǉ�

		JSONS.SaveJson(Json, "Save/Test.json");//�Z�[�u
		//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\//
		*/
}

void C_Player::End()
{
	if (m_pModel != nullptr)m_pModel = nullptr;
	if (CollisionModel != nullptr)CollisionModel = nullptr;
}


void C_Player::Update()
{
	if (PlayerPos.y > 0) {
		KdVec3 Vec(0.0f, 0.1f, 0.0f);
		PlayerPos -= Vec;
	}
	else PlayerPos.y = 0;


	if (ShopFlg);
	FlgProc();
	MoveProc();
	CameraProc();


	if (GetKey('8') & 0x8000) {
		//	�@�i�N���C�A���g���W�j�i�X�N���[�����W�j
		SetCursorPos(BasePt.x, BasePt.y);
		ShowCursor(FALSE);
	}
	if (GetKey('7') & 0x8000) {
		//	�@�i�N���C�A���g���W�j�i�X�N���[�����W�j
		SetCursorPos(BasePt.x, BasePt.y);
		ShowCursor(TRUE);
	}
	DTWHOUCE.SetVec("Player", PlayerPos);
	DTWHOUCE.SetFlg("Fishing", FishingFlg);

}


void C_Player::FlgProc()
{
	if (ShopFlg) {
		if (GetKey('I') & 0x8000) {
			DTWHOUCE.SetFlg("ShopFlg", true);
		}
		else DTWHOUCE.SetFlg("ShopFlg", false);
	}

	//�}�E�X�ł̃J�����ړ���on off
	if (GetKey('E') & 0x8000)
	{
		if (!ClickFlg)
		{
			ClickFlg = true;
			//�ނ胂�[�h����
			if (FishingFlg) {
				FishingFlg = false;
				RestoreFlg = true;

				DTWHOUCE.SetFlg("FishingFlg", false);
				ShowCursor(TRUE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
			else
			{
				//�ނ胂�[�h�Ɉڍs
				FishingFlg = true;
				DTWHOUCE.SetFlg("FishingFlg", true);
				ShowCursor(FALSE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
		}
	}
	else ClickFlg = false;


}

//�����蔻����܂ވړ�����
void C_Player::MoveProc()
{
	Move();
	HitObject();
}

//�ނ胂�[�h�łȂ���Έړ��ł���
void C_Player::Move()
{
	if (!FishingFlg) {
		if (GetKey('W') & 0x8000) {//�O��
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;


			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);

			//PlayerPos += Vec * MoveSpeed;
			MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 0);
			MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 0);

			/*
				bool B_SkipFlg = false;
				D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
				if (!B_SkipFlg)B_SkipFlg = MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 1);
				D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
				if (!B_SkipFlg)B_SkipFlg = MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 1);
				D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
				if (!B_SkipFlg)B_SkipFlg = MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 1);
			*/

			bool S_SkipFlg = false;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
		}
		if (GetKey('A') & 0x8000) {//��
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;

			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 0);
			MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 0);

			bool S_SkipFlg = false;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
		}
		if (GetKey('S') & 0x8000) {//����
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;

			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 0);
			MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 0);


			bool S_SkipFlg = false;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);

		}
		if (GetKey('D') & 0x8000) {//�E
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;

			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			MoveRay_Bridge(Vec, CollisionMat, CollisionModel->GetMesh(), 0);
			MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 0);


			bool S_SkipFlg = false;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			if (!S_SkipFlg)S_SkipFlg = MoveRay_Shop(Vec, ShopMat, ShopModel->GetMesh(), 1);
		}
	}

	TransMat.SetTrans(PlayerPos);
	D3DXMatrixRotationY(&PlayerRot, D3DXToRadian(CamAngY));

	m_world = PlayerRot * TransMat;
}

//������
void C_Player::HitObject()
{
	KdVec3 Vec(0.0f, -1.0f, 0.0f);

	static bool Stop = false;
	//���ׂ��蔻��i���b�V���j
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &CollisionMat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos + KdVec3(0, 1, 0)), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	DWORD PolyNo;	//�|���S���ԍ�
	D3DXIntersect(m_pModel->GetMesh(), &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &TextMeshDis2, NULL, NULL);

	if (TextMeshDis2 < 1) {
		PlayerPos.y += 1 - TextMeshDis2;
	}

	if (PlayerPos.y < 0) {
		PlayerPos.y = 0;
	}
}


void C_Player::CameraProc()
{
	//�ނ��Ԉڍs���̃J�����̓���
	CameraSet();

	//�}�E�X�֌W�̌v�Z
	MouseUpdate();
}
void C_Player::MouseUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	//�ނ胂�[�h����Ȃ��Ƃ��Ƀ}�E�X�ŃJ�����̉�]���ł���悤�Ɉړ�������
	if (!FishingFlg && !RestoreFlg)
	{
		long MoveX = (Pt.x - BasePt.x);
		if ((MoveX >= 3) || (MoveX <= -3)) {
			CamAngY += (Pt.x - BasePt.x) / 4.0f;
		}

		long MoveY = (Pt.y - BasePt.y);
		if ((MoveY >= 3) || (MoveY <= -3)) {
			CamAngX += (Pt.y - BasePt.y) / 4.0f;
		}
	}

	//�J�����̉�]�ő�l�𐧌�
	if (CamAngY < -180)	CamAngY = 180;
	if (CamAngY > 180)	CamAngY = -180;

	if (CamAngX < -80.0f) CamAngX = -80.0f;
	if (CamAngX > 40.0f && !RestoreFlg) CamAngX = 40.0f;

	if (!FishingFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static int cntY = 0;
	KdVec3 CamPos = CAMERA.GetCameraPos();		//�J�����̍��W������Ă���
	//�ނ胂�[�h���ǂ���
	if (FishingFlg)
	{
		if (cntY < 50) { cntY++; }
		else cntY = 50;

		//�J��������ɏグ�鏈��(�����_�̓u�C�̍��W)

		KdVec3 BuoyPos = DTWHOUCE.GetVec("Buoy");	//�u�C�̍��W������Ă���
		//�J�����̈ړ���
		float MoveSize = 0.1f;

		if (cntY < 50)CamPos.y += MoveSize;
		//		if (CamPos.y - PlayerPos.y < 5)CamPos.y += MoveSize;
		CAMERA.SetCameraPos(CamPos, BuoyPos);
	}
	else
	{
		if (cntY > 0)cntY--;
		else cntY = 0;

		//�J�����̈ʒu�������鏈��
		float MoveSize = 0.1f;

		if (cntY > 0)CamPos.y -= MoveSize;
		//if (CamPos.y - PlayerPos.y > 0)CamPos.y -= MoveSize;


		//�J�����̈ړ�����
		KdMatrix CamRot;
		KdVec3	 Vec;
		CamRot.CreateRotation(D3DXToRadian(CamAngX), D3DXToRadian(CamAngY), 0);
		D3DXVec3TransformCoord(&Vec, &CoordVec.Z, &CamRot);

		CamLook = Vec;
		CAMERA.SetCameraVec(PlayerPos + InitCamPos, Vec);
		RestoreFlg = false;
	}

}
/*
void C_Player::CameraSet()
{
	static KdVec3		CamPos;
	static KdVec3		CamLook;
	static float		_CamAngX;
	static bool			flg1 = false;
	static bool			flg2 = false;
	//�ނ胂�[�h���ƃJ�����͓������Ȃ��Ȃ�
	static bool			StopFlg = false;//�ނ胂�[�h�Ɉڍs�������̊Ԃ��������������p

	//�J�����̈ړ����I������Ƃ��ɕ����������悤�ɂ������
	if (flg1 && flg2) { BuoyFlg = true; }
	else { BuoyFlg = false; }

	//�ނ胂�[�h����Ȃ��Ƃ�
	if (!FishingFlg) {
		StopFlg = false;
		//�ނ胂�[�h���������ꂽ�Ƃ��A�J�����̉�]�����Ƃɖ߂�
		if (FishScene_CamAngX > 0) {
			FishScene_CamAngX -= 0.2f;
			if (RestoreFlg) {
				CamAngX -= 0.2f;
				flg1 = false;
			}
		}
		else FishScene_CamAngX = 0;

		//�������������ꂽ�Ƃ��ɃJ�����̈ʒu��߂�
		if (FishScene_CamPos.Length() > PlayerPos.y + FishScene_LenMin) {
			KdMatrix		CamRot;
			KdVec3			TmpVec;

			CamRot.SetRotation(0, D3DXToRadian(CamAngY), 0);
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Z, &CamRot);
			FishScene_CamPos -= TmpVec * 0.025f;
			D3DXVec3TransformCoord(&TmpVec, &CoordVec.Y, &CamRot);
			FishScene_CamPos -= TmpVec * 0.05f;
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
	if (FishingFlg) {
		if (!StopFlg) {
			FishScene_CamAngX = CamAngX;
			StopFlg = true;
		}
		//�J�����̃A���O����ύX����v���O����
		if (FishScene_CamAngX < CamAngX_MaxLimit)FishScene_CamAngX += 0.2f;
		else {
			FishScene_CamAngX = CamAngX_MaxLimit;
			flg1 = true;
		}

		//�J�����̈ʒu��ς���v���O����
		if (FishScene_CamPos.Length() < FishScene_LenMax + PlayerPos.y) {
			KdMatrix CamRot;
			KdVec3 TmpVec;

			CamRot.SetRotation(0, D3DXToRadian(CamAngY), 0);
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

		CamRot.SetRotation(D3DXToRadian(FishScene_CamAngX), D3DXToRadian(CamAngY), 0);
		D3DXVec3TransformCoord(&Vec, &CoordVec.Z, &CamRot);
		CamLook = Vec;

		CamPos = PlayerPos + FishScene_CamPos;
		CamAngX = FishScene_CamAngX;
	}


	CAMERA.SetCameraVec(CamPos, CamLook);
}
*/

void C_Player::Draw3D() {

	KD3D.SetWorldMatrix(&CollisionMat);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	CollisionModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}
void C_Player::Draw2D()
{
	SPRITE->End();
	char Text[100];
	RECT rcText = { 10,30 * 1,0,0 };
	sprintf_s(Text, sizeof(Text), "������ %d", (int)DTWHOUCE.GetNo("Possession"));
	FONT->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	//RECT rcText1 = { 10,30 * 7,0,0 };
	//sprintf_s(Text, sizeof(Text), "Dot %f", TextDot);
	//FONT->DrawText(NULL, Text, -1, &rcText1, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText2 = { 10,30 * 2,0,0 };
	sprintf_s(Text, sizeof(Text), "PlayerPos  x %f  y%f z %f ", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText2, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText3 = { 10,30 * 3,0,0 };
	if (!ShopFlg)FONT->DrawText(NULL, "ShopFlg=false", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else FONT->DrawText(NULL, "ShopFlg=true", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText4 = { 10,30 * 4,0,0 };
	if (!WallFlg)FONT->DrawText(NULL, "WallFlg=false", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else FONT->DrawText(NULL, "WallFlg=true", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	//RECT rcText5 = { 10,30 * 5,0,0 };
	//sprintf_s(Text, sizeof(Text), "TextDot2 %f ", TextDot2);
	//KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText5, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	//RECT rcText6 = { 10,30 * 6,0,0 };
	//sprintf_s(Text, sizeof(Text), "FishingScene_CamPos  x %f  y%f z %f ", FishScene_CamPos.x, FishScene_CamPos.y, FishScene_CamPos.z);
	//FONT->DrawText(NULL, Text, -1, &rcText6, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

}

//�����蔻��
bool C_Player::MoveRay_Shop(D3DXVECTOR3 Vec, KdMatrix Mat, LPD3DXBASEMESH lpMesh, int Mode)//Mode:0�Ȃ�X�Ƃ̓����蔻�� Mode:1�͓X�Ƃ̋����𑪂��ēX�ɓ���邩�ǂ���
{
	//���ׂ��蔻��i���b�V���j
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &Mat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	float MeshDis;
	DWORD PolyNo;	//�|���S���ԍ�
	D3DXIntersect(lpMesh, &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);


	float Dot = -1;

	if (Hit) {
		//���C����œ������Ă���|���S���̎���
		WORD* pI;
		lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		DWORD VertexNo[3];
		VertexNo[0] = *(pI + PolyNo * 3 + 0);
		VertexNo[1] = *(pI + PolyNo * 3 + 1);
		VertexNo[2] = *(pI + PolyNo * 3 + 2);

		lpMesh->UnlockIndexBuffer();


		CLONEVERTEX* pV;
		lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		D3DXVECTOR3		VPos[3];
		VPos[0] = (pV + VertexNo[0])->Pos;
		VPos[1] = (pV + VertexNo[1])->Pos;
		VPos[2] = (pV + VertexNo[2])->Pos;

		lpMesh->UnlockVertexBuffer();


		//�ǂ���v���O����	�O�p�`�̒�ʂƎΖʂ̃x�N�g�������    ����
		//�@���̎擾										�����灪
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &Mat);//������1��
		//						�@�@		 �A		�@ �B		�@ 1:3D��ԏ�ł̖@���̌����@
		//														   2:���b�V���쐬�p�̖@���̌���
		//														   3:�����p���b�V���̍s��
		D3DXVec3Normalize(&WallVec, &WallVec);//���K��
		//�@���̎擾����


		Dot = D3DXVec3Dot(&-WallVec, &(Vec * MeshDis));//�J�����̐i�s����
		float Limit = -2.0f;
		//�|���S������ǂꂾ�������ĕǂ��肷�邩�𒲐�('�D')

		//�������ǂ��菈���B
		//��������֎~�G���A�ƓX�ɓ����������Ɏ��M�𒵂˕Ԃ������ł��Q(�@_�L��`)_�߼�
		if (Mode != 1) {
			if (Dot > Limit && Dot < 0) {
				float Tmp = Limit - Dot;
				KdVec3 TmpVec = (Tmp * WallVec);
				TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
				PlayerPos += TmpVec;
			}

			Limit *= -1;
			//���̂�̓|���S���̗��ʂ����𔻒肷��̂ł������͕\�ʂ����肷��悤��
			//��������֎~�G���A�ɓ��������ɒ��˕Ԃ�����
			if (Dot < Limit && Dot > 0) {
				float Tmp = Limit - Dot;
				KdVec3 TmpVec = (Tmp * WallVec);
				TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
				PlayerPos += TmpVec;
			}
		}
	}

	//�V���b�v�ɓ��鏈��
	if (Mode == 0 || Mode == 1) {
		float Limit = 3;

		if (Dot < Limit && Dot>0) {
			//�V���b�v�ɓ��鏈��
			ShopFlg = true;
		}
		else {
			DTWHOUCE.SetFlg("ShopFlg", false);
			ShopFlg = false;
		}
	}
	DTWHOUCE.SetNo("Dot1", Dot);

	//�V���b�v�t���O���I���Ȃ�4�����ɍs���͂����������C�����r���ŃX�L�b�v
	//�t�@���X�Ȃ瑼�̕����̃��C������s���܂�(;'��')�����c
	if (ShopFlg)return true;
	else return false;
}
bool C_Player::MoveRay_Bridge(D3DXVECTOR3 Vec, KdMatrix Mat, LPD3DXBASEMESH lpMesh, int Mode)//Mode:1�Ȃ�X�Ƃ̓����蔻�� Mode:2�͓X�Ƃ̋����𑪂��ēX�ɓ���邩�ǂ���
{
	//���ׂ��蔻��i���b�V���j
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &Mat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	float MeshDis;
	DWORD PolyNo;	//�|���S���ԍ�
	D3DXIntersect(lpMesh, &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);


	float Dot = -1;

	if (Hit) {
		//���C����œ������Ă���|���S���̎���
		WORD* pI;
		lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		DWORD VertexNo[3];
		VertexNo[0] = *(pI + PolyNo * 3 + 0);
		VertexNo[1] = *(pI + PolyNo * 3 + 1);
		VertexNo[2] = *(pI + PolyNo * 3 + 2);

		lpMesh->UnlockIndexBuffer();


		CLONEVERTEX* pV;
		lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		D3DXVECTOR3		VPos[3];
		VPos[0] = (pV + VertexNo[0])->Pos;
		VPos[1] = (pV + VertexNo[1])->Pos;
		VPos[2] = (pV + VertexNo[2])->Pos;

		lpMesh->UnlockVertexBuffer();


		//�ǂ���v���O����	�O�p�`�̒�ʂƎΖʂ̃x�N�g�������    ����
		//�@���̎擾										�����灪
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &Mat);//������1��
		//						�@�@		 �A		�@ �B		�@ 1:3D��ԏ�ł̖@���̌����@
		//														   2:���b�V���쐬�p�̖@���̌���
		//														   3:�����p���b�V���̍s��
		D3DXVec3Normalize(&WallVec, &WallVec);//���K��
		//�@���̎擾����

		Dot = D3DXVec3Dot(&-WallVec, &(Vec * MeshDis));//Player�ƕǂ̋������v�Z

		//�|���S������ǂꂾ�������ĕǂ��肷�邩�𒲐�('�D')
		float Limit = -1.0f;
		WallFlg = false;

		//�������ǂ��菈���B
		//��������֎~�G���A�ƓX�ɓ����������Ɏ��M�𒵂˕Ԃ������ł��Q(�@_�L��`)_�߼�
		if (Dot > Limit && Dot < 0) {
			float Tmp = Limit - Dot;
			KdVec3 TmpVec = (Tmp * WallVec);
			TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
			PlayerPos += TmpVec;
			if (Mode == 1)
				WallFlg = true;
		}

		Limit *= -1;
		//���̂�̓|���S���̗��ʂ����𔻒肷��̂ł������͕\�ʂ����肷��悤��
		//��������֎~�G���A�ɓ��������ɒ��˕Ԃ�����
		if (Dot < Limit && Dot > 0) {
			float Tmp = Limit - Dot;
			KdVec3 TmpVec = (Tmp * WallVec);
			TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
			PlayerPos += TmpVec;
			if (Mode == 1)	WallFlg = true;
		}
	}


	if (Mode == 0)PlayerPos += Vec * MoveSpeed;

	if (Mode == 1) {
		if (WallFlg)return true;
		else return false;
	}
	return false;
}