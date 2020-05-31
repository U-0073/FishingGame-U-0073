#include "../System/KdLibrary/KdLibrary.h"
#include "C_Player.h"
#include "../System/FrameBase/CGameFrame.h"


#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

C_Player::C_Player()
{
}

C_Player::~C_Player()
{
}

void C_Player::Init()
{
	PlayerPos = { 0,0,0 };
	CAMERA.SetCameraVec(PlayerPos + InitCamPos, KdVec3(0, 0, 1));
	CollisionMat.SetTrans(0.0f, -1.5f, 0.0f);
	ShopMat.SetTrans(14, -0.6f, -42);

	CollisionModel = RESOURCE_MNG.GetModel("PortWall_CollisionTest2");
	m_pModel = RESOURCE_MNG.GetModel("Portfloor_Collision");
	ShopModel = RESOURCE_MNG.GetModel("Shop");




	//ポインター関係
	BasePt.x = SCRW / 2;
	BasePt.y = SCRH / 2;
	ClientToScreen(FRAME.GetHWND(), &BasePt);		//ゲーム画面内座標⇒パソコン画面内座標
										//	　（クライアント座標）（スクリーン座標）
	SetCursorPos(BasePt.x, BasePt.y);

	enterTex = RESOURCE_MNG.GetTexture("enterKey.png");
	enterMat.SetTrans(1280 / 2, 720 / 3, 0);

}

void C_Player::End()
{
	m_pModel = nullptr;
	CollisionModel = nullptr;
	enterTex = nullptr;
}


void C_Player::Update()
{
	if (PlayerPos.y > 0) {
		KdVec3 Vec(0.0f, 0.1f, 0.0f);
		PlayerPos -= Vec;
	}
	else PlayerPos.y = 0;


	FlgProc();
	MoveProc();
	CameraProc();

	DTWHOUCE.SetVec("Player", PlayerPos);
	DTWHOUCE.SetFlg("Fishing", FishingFlg);

}


void C_Player::FlgProc()
{
	if (ShopFlg) {
		if (GetKey(VK_RETURN) & 0x8000) {
			DTWHOUCE.SetFlg("ShopFlg", true);
		}
		else DTWHOUCE.SetFlg("ShopFlg", false);
	}

	//マウスでのカメラ移動のon off
	if (!BuoiRay())
	{
		if (GetKey('E') & 0x8000)
		{
			if (!ClickFlg)
			{
				ClickFlg = true;
				//釣りモード解除
				if (FishingFlg) {
					FishingFlg = false;

					DTWHOUCE.SetFlg("FishingFlg", false);
					SetCursorPos(BasePt.x, BasePt.y);
				}
				else
				{
					//釣りモードに移行
					FishingFlg = true;
					DTWHOUCE.SetFlg("FishingFlg", true);
					SetCursorPos(BasePt.x, BasePt.y);
				}
			}
		}
		else ClickFlg = false;
	}


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
	static float MeshDis;//本来ならfloat　MeshDisでいいが、今回モデルの関係で隙間ができてるため、そこに到達したら次元のはざまに飛ばされる(´・ω・`)

	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(m_pModel->GetMesh(), &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);

	if (MeshDis < 1) {
		PlayerPos.y += 1 - MeshDis;
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
	if (!FishingFlg)
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
	if (CamAngX > 60.0f) CamAngX = 60.0f;

	if (!FishingFlg) SetCursorPos(BasePt.x, BasePt.y);
}
void C_Player::CameraSet()
{
	static float TmpCamAngX = 0;
	static KdVec3 TmpCamPosY;
	static KdVec3 TmpCamPosZ;
	static KdVec3	 TmpVec;
	static int cntY = 0;
	KdMatrix CamRot;
	KdVec3	 Vec;

	KdVec3 CamPos = PlayerPos + InitCamPos;		//カメラの座標を取ってくる
	//釣りモードかどうか
	if (FishingFlg)
	{
		if (cntY < 50)cntY++;
		else cntY = 50;

		//カメラを上に上げる処理(注視点はブイの座標)
		//KdVec3 BuoyPos = DTWHOUCE.GetVec("Buoy");	//ブイの座標を取ってくる

		//カメラの移動量
		float MoveSize = 0.1f;

		//if (cntY < 50)CamPos.y += MoveSize;
		if (cntY < 50) {
			TmpCamPosY.y += MoveSize;
			if (cntY > 30)TmpCamPosZ.z += 0.05f;

			CamPos.y += MoveSize;

		}
		if (CamAngX < 40)
			CamAngX += 0.4;

		//CAMERA.SetCameraPos(CamPos, BuoyPos);
	}
	else
	{
		if (cntY > 0)cntY--;
		else cntY = 0;

		//if (cntY > 0)CamPos.y -= MoveSize;
		//カメラの位置を下げる処理
		float MoveSize = 0.1f;

		if (cntY > 0) {
			if (CamAngX > 0)
				CamAngX -= 0.4;
			if (cntY > 30)TmpCamPosZ.z -= 0.05f;
			else TmpCamPosZ.z = 0;
			//CamPos.y -= MoveSize;
			TmpCamPosY.y -= MoveSize;
		}
		else TmpCamPosY.y = 0;

	}

	CamRot.CreateRotation(D3DXToRadian(CamAngX + TmpCamAngX), D3DXToRadian(CamAngY), 0);
	D3DXVec3TransformCoord(&Vec, &CoordVec.Z, &CamRot);

	CamRot.CreateRotationY(D3DXToRadian(CamAngY));
	D3DXVec3TransformCoord(&TmpVec, &TmpCamPosZ, &CamRot);

	CamLook = Vec;
	CAMERA.SetCameraVec((CamPos + TmpCamPosY + TmpVec), Vec);
}

void C_Player::Draw3D() {

	KD3D.SetWorldMatrix(&CollisionMat);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	CollisionModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}
void C_Player::Draw2D()
{

	if (ShopFlg) {
		RECT rcEnter = { 0,0,200,200 };
		SPRITE->SetTransform(&enterMat);
		SPRITE->Draw(*enterTex, &rcEnter, &D3DXVECTOR3(200 / 2, 200 / 2, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}



	SPRITE->End();

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

}


bool C_Player::BuoiRay()
{
	KdVec3 Vec(0.0f, 1.0f, 0.0f);

	static bool Stop = false;
	//かべずり判定（メッシュ）
	D3DXMATRIX	InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &CollisionMat);
	D3DXVECTOR3	LocalPos, LocalVec;


	KdMatrix CamRot;
	KdVec3	 CamVec;
	CamRot.CreateRotationY(D3DXToRadian(CamAngY));
	D3DXVec3TransformCoord(&CamVec, &CoordVec.Z, &CamRot);
	DTWHOUCE.SetVec("CamVecY", CamVec);

	D3DXVec3TransformCoord(&LocalPos, &(PlayerPos + KdVec3(0, -PlayerPos.y - 1.0f, 0) + (CamVec * 15)), &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &Vec, &InvMat);

	BOOL Hit;
	static float MeshDis;//本来ならfloat　MeshDisでいいが、今回モデルの関係で隙間ができてるため、そこに到達したら次元のはざまに飛ばされる(´・ω・`)

	DWORD PolyNo;	//ポリゴン番号
	D3DXIntersect(m_pModel->GetMesh(), &LocalPos, &LocalVec, &Hit,
		&PolyNo, NULL, NULL, &MeshDis, NULL, NULL);

	if (Hit)
	{
		return true;
	}
	return false;
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


	float Dot = -3;
	WallDot = Dot;

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
		WallDot = Dot;

		//ポリゴンからどれだけ離して壁ずりするかを調整('Д')
		float Limit = -1.0f;
		WallFlg = false;

		if (Mode != 2) {
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
	}


	if (Mode == 0)PlayerPos += Vec * MoveSpeed;

	if (Mode == 1) {
		if (WallFlg)return true;
		else return false;
	}
	return false;
}