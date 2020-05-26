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




	//ポインター関係
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//ゲーム画面内座標⇒パソコン画面内座標
										//	　（クライアント座標）（スクリーン座標）
	SetCursorPos(BasePt.x, BasePt.y);
	ShowCursor(FALSE);
	/*
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
		//	　（クライアント座標）（スクリーン座標）
		SetCursorPos(BasePt.x, BasePt.y);
		ShowCursor(FALSE);
	}
	if (GetKey('7') & 0x8000) {
		//	　（クライアント座標）（スクリーン座標）
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

	//マウスでのカメラ移動のon off
	if (GetKey('E') & 0x8000)
	{
		if (!ClickFlg)
		{
			ClickFlg = true;
			//釣りモード解除
			if (FishingFlg) {
				FishingFlg = false;
				RestoreFlg = true;

				DTWHOUCE.SetFlg("FishingFlg", false);
				ShowCursor(TRUE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
			else
			{
				//釣りモードに移行
				FishingFlg = true;
				DTWHOUCE.SetFlg("FishingFlg", true);
				ShowCursor(FALSE);
				SetCursorPos(BasePt.x, BasePt.y);
			}
		}
	}
	else ClickFlg = false;


}

//当たり判定を含む移動処理
void C_Player::MoveProc()
{
	Move();
	HitObject();
}

//釣りモードでなければ移動できる
void C_Player::Move()
{
	if (!FishingFlg) {
		if (GetKey('W') & 0x8000) {//前へ
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
		if (GetKey('A') & 0x8000) {//左
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
		if (GetKey('S') & 0x8000) {//後ろへ
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
		if (GetKey('D') & 0x8000) {//右
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

//床判定
void C_Player::HitObject()
{
	KdVec3 Vec(0.0f, -1.0f, 0.0f);

	static bool Stop = false;
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &CollisionMat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos + KdVec3(0, 1, 0)), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	DWORD PolyNo;	//ポリゴン番号
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
	//釣り状態移行時のカメラの動き
	CameraSet();

	//マウス関係の計算
	MouseUpdate();
}
void C_Player::MouseUpdate() {
	POINT Pt;
	GetCursorPos(&Pt);

	//釣りモードじゃないときにマウスでカメラの回転をできるように移動させる
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

	//カメラの回転最大値を制限
	if (CamAngY < -180)	CamAngY = 180;
	if (CamAngY > 180)	CamAngY = -180;

	if (CamAngX < -80.0f) CamAngX = -80.0f;
	if (CamAngX > 40.0f && !RestoreFlg) CamAngX = 40.0f;

	if (!FishingFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static int cntY = 0;
	KdVec3 CamPos = CAMERA.GetCameraPos();		//カメラの座標を取ってくる
	//釣りモードかどうか
	if (FishingFlg)
	{
		if (cntY < 50) { cntY++; }
		else cntY = 50;

		//カメラを上に上げる処理(注視点はブイの座標)

		KdVec3 BuoyPos = DTWHOUCE.GetVec("Buoy");	//ブイの座標を取ってくる
		//カメラの移動量
		float MoveSize = 0.1f;

		if (cntY < 50)CamPos.y += MoveSize;
		//		if (CamPos.y - PlayerPos.y < 5)CamPos.y += MoveSize;
		CAMERA.SetCameraPos(CamPos, BuoyPos);
	}
	else
	{
		if (cntY > 0)cntY--;
		else cntY = 0;

		//カメラの位置を下げる処理
		float MoveSize = 0.1f;

		if (cntY > 0)CamPos.y -= MoveSize;
		//if (CamPos.y - PlayerPos.y > 0)CamPos.y -= MoveSize;


		//カメラの移動処理
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
	//釣りモードだとカメラは動かせなくなる
	static bool			StopFlg = false;//釣りモードに移行した一回の間だけ動かす処理用

	//カメラの移動が終わったときに浮きが浮くようにするもの
	if (flg1 && flg2) { BuoyFlg = true; }
	else { BuoyFlg = false; }

	//釣りモードじゃないとき
	if (!FishingFlg) {
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

	//釣りモードの時
	if (FishingFlg) {
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
	sprintf_s(Text, sizeof(Text), "所持金 %d", (int)DTWHOUCE.GetNo("Possession"));
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

//当たり判定
bool C_Player::MoveRay_Shop(D3DXVECTOR3 Vec, KdMatrix Mat, LPD3DXBASEMESH lpMesh, int Mode)//Mode:0なら店との当たり判定 Mode:1は店との距離を測って店に入れるかどうか
{
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &Mat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	float MeshDis;
	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(lpMesh, &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);


	float Dot = -1;

	if (Hit) {
		//レイ判定で当たっているポリゴンの識別
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


		//壁ずりプログラム	三角形の底面と斜面のベクトルを入手    →△
		//法線の取得										こいつら↑
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &Mat);//長さを1に
		//						　①		 ②		　 ③		　 1:3D空間上での法線の向き　
		//														   2:メッシュ作成用の法線の向き
		//														   3:建物用メッシュの行列
		D3DXVec3Normalize(&WallVec, &WallVec);//正規化
		//法線の取得完了


		Dot = D3DXVec3Dot(&-WallVec, &(Vec * MeshDis));//カメラの進行方向
		float Limit = -2.0f;
		//ポリゴンからどれだけ離して壁ずりするかを調整('Д')

		//ここが壁ずり処理。
		//立ち入り禁止エリアと店に当たった時に自信を跳ね返す処理です＿(　_´ω`)_ﾍﾟｼｮ
		if (Mode != 1) {
			if (Dot > Limit && Dot < 0) {
				float Tmp = Limit - Dot;
				KdVec3 TmpVec = (Tmp * WallVec);
				TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
				PlayerPos += TmpVec;
			}

			Limit *= -1;
			//↑のやつはポリゴンの裏面だけを判定するのでこっちは表面も判定するように
			//立ち入り禁止エリアに入った時に跳ね返す処理
			if (Dot < Limit && Dot > 0) {
				float Tmp = Limit - Dot;
				KdVec3 TmpVec = (Tmp * WallVec);
				TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
				PlayerPos += TmpVec;
			}
		}
	}

	//ショップに入る処理
	if (Mode == 0 || Mode == 1) {
		float Limit = 3;

		if (Dot < Limit && Dot>0) {
			//ショップに入る処理
			ShopFlg = true;
		}
		else {
			DTWHOUCE.SetFlg("ShopFlg", false);
			ShopFlg = false;
		}
	}
	DTWHOUCE.SetNo("Dot1", Dot);

	//ショップフラグがオンなら4方向に行うはずだったレイ判定を途中でスキップ
	//ファルスなら他の方向のレイ判定を行います(;'∀')ﾁｶﾚﾀ…
	if (ShopFlg)return true;
	else return false;
}
bool C_Player::MoveRay_Bridge(D3DXVECTOR3 Vec, KdMatrix Mat, LPD3DXBASEMESH lpMesh, int Mode)//Mode:1なら店との当たり判定 Mode:2は店との距離を測って店に入れるかどうか
{
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &Mat);
	D3DXVECTOR3	LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	float MeshDis;
	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(lpMesh, &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);


	float Dot = -1;

	if (Hit) {
		//レイ判定で当たっているポリゴンの識別
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


		//壁ずりプログラム	三角形の底面と斜面のベクトルを入手    →△
		//法線の取得										こいつら↑
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &Mat);//長さを1に
		//						　①		 ②		　 ③		　 1:3D空間上での法線の向き　
		//														   2:メッシュ作成用の法線の向き
		//														   3:建物用メッシュの行列
		D3DXVec3Normalize(&WallVec, &WallVec);//正規化
		//法線の取得完了

		Dot = D3DXVec3Dot(&-WallVec, &(Vec * MeshDis));//Playerと壁の距離を計算

		//ポリゴンからどれだけ離して壁ずりするかを調整('Д')
		float Limit = -1.0f;
		WallFlg = false;

		//ここが壁ずり処理。
		//立ち入り禁止エリアと店に当たった時に自信を跳ね返す処理です＿(　_´ω`)_ﾍﾟｼｮ
		if (Dot > Limit && Dot < 0) {
			float Tmp = Limit - Dot;
			KdVec3 TmpVec = (Tmp * WallVec);
			TmpVec.Set(TmpVec.x, 0.0f, TmpVec.z);
			PlayerPos += TmpVec;
			if (Mode == 1)
				WallFlg = true;
		}

		Limit *= -1;
		//↑のやつはポリゴンの裏面だけを判定するのでこっちは表面も判定するように
		//立ち入り禁止エリアに入った時に跳ね返す処理
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