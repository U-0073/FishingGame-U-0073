#include"../System/KdLibrary/KdLibrary.h"
#include "Sea.h"

Sea::Sea()
{
	

	srand(timeGetTime());
	//�����̐ݒ�
	for (int i = 0; i < VIRTICAL + 1; i++) {
		for (int k = 0; k < SIDE + 1; k++) {
			Height[i][k] = 0;
		}
	}
	KD3D.LoadTexture(&vTex,"Resouce/Texture/�C��.jpg",1024,1024,NULL);
	//setTexParam("Resouce/Texture/HP_G.png", 3, 3,/*NULL*/ D3DCOLOR_ARGB(255, 255, 255, 255));
	//RESOURCE_MNG.LoadTexture(&vTex, "Resouce/Texture/Ground.bmp", 1024, 1024, NULL);
}

Sea::~Sea()
{
}


void Sea::Draw()
{
	KD3D.GetDev()->SetTexture(0, NULL);

	//���_���ƂɐF���w��
	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	KD3D.GetDev()->SetFVF(FVF_VERTEX);

	//���C�g�̌v�Z���I�t�ɂ���
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`��ʒu�̎w��(�|���̒��S���W)
	D3DXMATRIX TransMat;

	for (int i = 0; i < VIRTICAL; i++) {
		for (int k = 0; k < SIDE; k++) {


			//����O���玞�v���
			//�|���̒��S��0�C0�C0�ƒu�������W
			v[0].Pos = D3DXVECTOR3(0.0f, Height[i][k], 0.0f);
			v[1].Pos = D3DXVECTOR3(0.0f, Height[i][k + 1], 5.0f);
			v[2].Pos = D3DXVECTOR3(5.0f, Height[i + 1][k + 1], 5.0f);
			v[3].Pos = D3DXVECTOR3(5.0f, Height[i + 1][k], 0.0f);

			//�摜�̂ǂ���|���ɕ`�悷��̂�
			//0.0�`1.0�܂łŎw��
			v[0].Tex = D3DXVECTOR2((float)k / SIDE, (float)i / VIRTICAL);
			v[1].Tex = D3DXVECTOR2((float)(k + 1) / SIDE, (float)i / VIRTICAL);
			v[2].Tex = D3DXVECTOR2((float)(k + 1) / SIDE, (float)(i + 1) / VIRTICAL);
			v[3].Tex = D3DXVECTOR2((float)k / SIDE, (float)(i + 1) / VIRTICAL);

			D3DXMatrixTranslation(&TransMat, (k * 5) - 150, -3.0f, (i * 5) - 50);
			KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
			KD3D.GetDev()->SetTransform(D3DTS_WORLD, &TransMat);
			KD3D.GetDev()->SetTexture(0, vTex);

			//RESOURCE_MNG.GetTexture(vTex, mPath, mW, mH, mColor);

			//KD3D.GetDev()->SetTexture(0, RESOURCE_MNG.GetTexture(mPath, mW, mH, NULL));



			KD3D.GetDev()->SetFVF(FVF_VERTEX);
			KD3D.GetDev()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
			KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
	//KD3D.GetDev()->SetTexture(0, NULL);


}

//���C����
float Sea::Ray_Judge(D3DXVECTOR3 Pos)
{
	//���C����Ɏg�����߂�
	//�����̍��W�̐^���ɂ���|���S��
	//�ꖇ������Ă���
	int NowX, NowZ;
	NowX = (int)(Pos.x / 10);
	NowZ = (int)(Pos.z / 10);
	D3DXVECTOR3 vPos[4];
	vPos[0] = D3DXVECTOR3(NowX * 10.0f, Height[NowX][NowZ], NowZ * 10.0f);
	vPos[1] = D3DXVECTOR3(NowX * 10.0f, Height[NowX][NowZ + 1], (NowZ + 1) * 10.0f);
	vPos[2] = D3DXVECTOR3((NowX + 1) * 10.0f, Height[NowX + 1][NowZ + 1], (NowZ + 1) * 10.0f);
	vPos[3] = D3DXVECTOR3((NowX + 1) * 10.0f, Height[NowX + 1][NowZ], NowZ * 10.0f);

	//�������烌�C����
	float Dis;
	if (D3DXIntersectTri(&vPos[0], &vPos[1], &vPos[2], &Pos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis) ||
		D3DXIntersectTri(&vPos[0], &vPos[2], &vPos[3], &Pos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis))
	{
	}
	return Dis;
}
