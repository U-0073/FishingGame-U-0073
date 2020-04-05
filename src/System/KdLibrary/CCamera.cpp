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

//�G��Ȃ���
void CCamera::Set(const D3DXVECTOR2& mWindowSize)
{
	
	D3DXMATRIX mView, mProj;

	D3DXVECTOR3 LookPos=Pos+LookVec;
	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		//&D3DXVECTOR3(0.0f, 0.0f, -10.0f),	// �J�����̈ʒu
		&Pos,
		//&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �J�����̎��_
		&LookPos,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), mWindowSize.x / mWindowSize.y, 1.0f, 1000.0f);

	//�s��ݒ�
	KD3D.GetDev()->SetTransform(D3DTS_VIEW, &mView);
	KD3D.GetDev()->SetTransform(D3DTS_PROJECTION, &mProj);

}

//�J�����̈ʒu�ƌ����Ăق��������x�N�g����n��
void CCamera::SetCameraPoss(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _LookVec)
{
	Pos = _Pos;
	LookVec = _LookVec;
}


