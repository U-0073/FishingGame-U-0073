#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"
#include "../System/FrameBase/CGameFrame.h"


#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
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
	CollisionMat.CreateTrans(0.0f, -1.5f, 0.0f);
	CollisionModel = RESOURCE_MNG.GetModel("./Resource/3DModel/PortWall_Collision.x");
	m_pModel = RESOURCE_MNG.GetModel("./Resource/3DModel/Port.x");

	//ポインター関係
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//ゲーム画面内座標⇒パソコン画面内座標
										//	　（クライアント座標）（スクリーン座標）
	SetCursorPos(BasePt.x, BasePt.y);
	ShowCursor(FALSE);




	//―――――――――――――以下Json使用例――――――――――――//
	auto Json = std::make_shared<json11::Json>();
	Json = JSONS.LoadJson("Default/Test.json");//読み込み
	std::string tag = "Player";//VisualStudioバグ対策でstringは一度宣言してから入れて

	bool test1 = JSONS.checkValue(Json, "Tag", tag);//文字列比較
	test1 = JSONS.checkValue(Json, "Tag", 111);//数字と比較
	//まだ使えない
	JSONS.AddKeyValue(Json, "Value5", std::string("ABCD"));//要素の変更、追加

	JSONS.SaveJson(Json, "Save/Test.json");//セーブ
	//――――――――――――――――――――――――――――――――//
}
void C_Player::Begin()
{
}
void C_Player::End()
{
	CollisionModel = nullptr;
}


void C_Player::Update()
{
	if (GetKey('Z') & 0x8000) {//前へ
		KdVec3 Vec(0.0f, 0.1f, 0.0f);
		if (PlayerPos.y > 0)PlayerPos -= Vec;
		else PlayerPos.y = 0;
	}
	if (GetKey('X') & 0x8000) {//前へ
		KdVec3 Vec(0.0f, 0.1f, 0.0f);
		PlayerPos += Vec;
	}


	FlgProc();
	MoveProc();
	CameraProc();

}


void C_Player::FlgProc()
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
	Earth();
	Move();
}

void C_Player::Move()
{
	bool	MoveFlg = false;

	if (!FishFlg) {
		if (GetKey('W') & 0x8000) {//前へ
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Front, &RotMat);

			MoveRay(Vec);
		}
		if (GetKey('A') & 0x8000) {//左
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Left, &RotMat);
			MoveRay(Vec);
		}
		if (GetKey('S') & 0x8000) {//後ろへ
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Back, &RotMat);
			MoveRay(Vec);
		}
		if (GetKey('D') & 0x8000) {//右
			D3DXMATRIX RotMat;
			D3DXMatrixRotationY(&RotMat, D3DXToRadian(CamAngY));
			D3DXVECTOR3	Vec;
			D3DXVec3TransformCoord(&Vec, &CoordVec.Right, &RotMat);
			MoveRay(Vec);
		}
	}

	TransMat.CreateTrans(PlayerPos);
	D3DXMatrixRotationY(&PlayerRot, D3DXToRadian(CamAngY));
	m_world = PlayerRot * TransMat;
}

void C_Player::Earth()
{
	KdVec3 Vec(0.0f, -1.0f, 0.0f);
	KdVec3 TmpPos(0.0f, 1.0f, 0.0f);

	static bool Stop = false;
	static float TmpDis;
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &CollisionMat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos + TmpPos), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(m_pModel->GetMesh(), &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &TextMeshDis, NULL, NULL);


	if (!Stop) {
		TmpDis = TextMeshDis;
		Stop = true;
	}
	//PlayerPos.y = TextMeshDis -TmpDis;
}


void C_Player::CameraProc()
{
	if (!FishFlg && !RestoreFlg) {
		if (GetKey(VK_RIGHT) & 0x8000) {
			CamAngY += 1.0f;
		}
		if (GetKey(VK_LEFT) & 0x8000) {
			CamAngY -= 1.0f;
		}
		if (GetKey(VK_UP) & 0x8000) {
			CamAngX -= 1.0f;
		}
		if (GetKey(VK_DOWN) & 0x8000) {
			CamAngX += 1.0f;
		}
	}

	//釣り状態移行時のカメラの動き
	CameraSet();

	//マウス関係の計算
	MouseUpdate();
}
void C_Player::MouseUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	//釣りモードじゃないときにマウスでカメラの回転をできるように移動させる
	if (!FishFlg && !RestoreFlg)
	{
		long MoveX = (Pt.x - BasePt.x);
		if ((MoveX >= 3) || (MoveX <= -3)){
			CamAngY += (Pt.x - BasePt.x) / 4.0f;
		}

		long MoveY = (Pt.y - BasePt.y);
		if ((MoveY >= 3) || (MoveY <= -3)){
			CamAngX += (Pt.y - BasePt.y) / 4.0f;
		}
	}

	//カメラの回転最大値を制限
	if (CamAngY < -180)	CamAngY = 180;
	if (CamAngY > 180)	CamAngY = -180;

	if (CamAngX < -80.0f) CamAngX = -80.0f;
	if (CamAngX > 40.0f && !RestoreFlg) CamAngX = 40.0f;

	if (!FishFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static KdVec3		CamPos;
	static KdVec3		CamLook;
	static float		_CamAngX;
	static bool			flg1 = false;
	static bool			flg2 = false;
	static bool			StopFlg = false;//釣りモードに移行した一回の間だけ動かす処理用

	//カメラの移動が終わったときに浮きが浮くようにするもの
	if (flg1 && flg2) { BuoiFlg = true; }
	else { BuoiFlg = false; }

	//釣りモードじゃないとき
	if (!FishFlg) {
		StopFlg = false;
		//釣りモードが解除されたとき、カメラの回転をもとに戻す
		if (FishScene_CamAngX > 0) {
			FishScene_CamAngX -= 0.2f;
			if (RestoreFlg) {
				CamAngX -= 0.2f;
				flg1 = false;
			}
		}
		else FishScene_CamAngX = 0;

		//同じく解除されたときにカメラの位置を戻す
		if (FishScene_CamPos.Length() > PlayerPos.y + FishScene_LenMin) {
			KdMatrix		CamRot;
			KdVec3			TmpVec;

			CamRot.CreateRotationY(D3DXToRadian(CamAngY));
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

	//釣りモードの時
	if (FishFlg) {
		if (!StopFlg) {
			FishScene_CamAngX = CamAngX;
			StopFlg = true;
		}
		//カメラのアングルを変更するプログラム
		if (FishScene_CamAngX < CamAngX_MaxLimit)FishScene_CamAngX += 0.2f;
		else {
			FishScene_CamAngX = CamAngX_MaxLimit;
			flg1 = true;
		}

		//カメラの位置を変えるプログラム
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

	KD3D.SetWorldMatrix(&CollisionMat);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	//CollisionModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	Draw3DWall();
}
void C_Player::Draw2D()
{
	SPRITE->End();
	char Text[100];
	RECT rcText = { 10,30 * 1,0,0 };
	sprintf_s(Text, sizeof(Text), "FishSceneLength %f", FishScene_CamPos.Length());
	FONT->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText1 = { 10,30 * 7,0,0 };
	sprintf_s(Text, sizeof(Text), "FishSceneCamAng x %f CamAng x %f  y%f", FishScene_CamAngX, CamAngX, CamAngY);
	FONT->DrawText(NULL, Text, -1, &rcText1, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText2 = { 10,30 * 2,0,0 };
	sprintf_s(Text, sizeof(Text), "PlayerPos  x %f  y%f z %f ", PlayerPos.x, PlayerPos.y, PlayerPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText2, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText3 = { 10,30 * 3,0,0 };
	if (!RestoreFlg)FONT->DrawText(NULL, "RestoreFlg=false", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else FONT->DrawText(NULL, "RestoreFlg=true", -1, &rcText3, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText4 = { 10,30 * 4,0,0 };
	if (!FishFlg)FONT->DrawText(NULL, "FishFlg=false", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	else FONT->DrawText(NULL, "FishFlg=true", -1, &rcText4, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText5 = { 10,30 * 5,0,0 };
	sprintf_s(Text, sizeof(Text), "MeshDisY %f ", TextMeshDis);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText5, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	RECT rcText6 = { 10,30 * 6,0,0 };
	sprintf_s(Text, sizeof(Text), "FishingScene_CamPos  x %f  y%f z %f ", FishScene_CamPos.x, FishScene_CamPos.y, FishScene_CamPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText6, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

}


void C_Player::MoveRay(D3DXVECTOR3 Vec)
{
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &CollisionMat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &PlayerPos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	float MeshDis;
	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(CollisionModel->GetMesh(), &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);


	if (Hit) {
		//レイ判定で当たっているポリゴンの識別
		WORD* pI;
		CollisionModel->GetMesh()->LockIndexBuffer(0, (LPVOID*)&pI);
		DWORD VertexNo[3];
		VertexNo[0] = *(pI + PolyNo * 3 + 0);
		VertexNo[1] = *(pI + PolyNo * 3 + 1);
		VertexNo[2] = *(pI + PolyNo * 3 + 2);

		CollisionModel->GetMesh()->UnlockIndexBuffer();


		CLONEVERTEX* pV;
		CollisionModel->GetMesh()->LockVertexBuffer(0, (LPVOID*)&pV);
		D3DXVECTOR3		VPos[3];
		VPos[0] = (pV + VertexNo[0])->Pos;
		VPos[1] = (pV + VertexNo[1])->Pos;
		VPos[2] = (pV + VertexNo[2])->Pos;

		CollisionModel->GetMesh()->UnlockVertexBuffer();


		//壁ずりプログラム	三角形の底面と斜面のベクトルを入手    →△
		//法線の取得										こいつら↑
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &CollisionMat);//長さを1に
		//						　①		 ②		　 ③		　 1:3D空間上での法線の向き　
		//														   2:メッシュ作成用の法線の向き
		//														   3:建物用メッシュの行列
		D3DXVec3Normalize(&WallVec, &WallVec);//正規化
		//法線の取得完了


		float Dot;
		Dot = D3DXVec3Dot(&WallVec, &-Vec);//カメラの進行方向
		float Limit;
		Limit = 2 / Dot;
		if (Limit < 0)Limit *= -1;
		if (MeshDis < Limit) {

			KdVec3 TmpVec = WallVec * ((Limit - MeshDis) * Dot);
			TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
			PlayerPos += TmpVec;//法線方向に押し出す
		}
	}
	PlayerPos += Vec * MoveSpeed;
}
