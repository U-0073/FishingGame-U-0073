#include"../KdLibrary/KdLibrary.h"
#include "CCamera.h"



CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

/*CMasterCamera * CGameCamera::GetCamera(void)
{
	return this;
}*/

//触らないで
void CCamera::Set(const D3DXVECTOR2& mWindowSize)
{
	
	D3DXMATRIX mView, mProj;

	D3DXVECTOR3 LookPos=Pos+LookVec;
	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		//&D3DXVECTOR3(0.0f, 0.0f, -10.0f),	// カメラの位置
		&Pos,
		//&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// カメラの視点
		&LookPos,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), mWindowSize.x / mWindowSize.y, 1.0f, 1000.0f);

	//行列設定
	KD3D.GetDev()->SetTransform(D3DTS_VIEW, &mView);
	KD3D.GetDev()->SetTransform(D3DTS_PROJECTION, &mProj);

}

//カメラの位置と向いてほしい方向ベクトルを渡す
void CCamera::SetCameraPoss(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _LookVec)
{
	Pos = _Pos;
	LookVec = _LookVec;
}


