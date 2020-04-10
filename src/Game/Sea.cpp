#include"../System/KdLibrary/KdLibrary.h"
#include "Sea.h"

Sea::Sea()
{
	

	srand(timeGetTime());
	//高さの設定
	for (int i = 0; i < VIRTICAL + 1; i++) {
		for (int k = 0; k < SIDE + 1; k++) {
			Height[i][k] = 0;
		}
	}
	KD3D.LoadTexture(&vTex,"Resouce/Texture/海面.jpg",1024,1024,NULL);
	//setTexParam("Resouce/Texture/HP_G.png", 3, 3,/*NULL*/ D3DCOLOR_ARGB(255, 255, 255, 255));
	//RESOURCE_MNG.LoadTexture(&vTex, "Resouce/Texture/Ground.bmp", 1024, 1024, NULL);
}

Sea::~Sea()
{
}


void Sea::Draw()
{
	KD3D.GetDev()->SetTexture(0, NULL);

	//頂点ごとに色を指定
	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	KD3D.GetDev()->SetFVF(FVF_VERTEX);

	//ライトの計算をオフにする
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画位置の指定(板ポリの中心座標)
	D3DXMATRIX TransMat;

	for (int i = 0; i < VIRTICAL; i++) {
		for (int k = 0; k < SIDE; k++) {


			//左手前から時計回り
			//板ポリの中心を0，0，0と置いた座標
			v[0].Pos = D3DXVECTOR3(0.0f, Height[i][k], 0.0f);
			v[1].Pos = D3DXVECTOR3(0.0f, Height[i][k + 1], 5.0f);
			v[2].Pos = D3DXVECTOR3(5.0f, Height[i + 1][k + 1], 5.0f);
			v[3].Pos = D3DXVECTOR3(5.0f, Height[i + 1][k], 0.0f);

			//画像のどこを板ポリに描画するのか
			//0.0～1.0までで指定
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

//レイ判定
float Sea::Ray_Judge(D3DXVECTOR3 Pos)
{
	//レイ判定に使うために
	//自分の座標の真下にあるポリゴン
	//一枚を取ってくる
	int NowX, NowZ;
	NowX = (int)(Pos.x / 10);
	NowZ = (int)(Pos.z / 10);
	D3DXVECTOR3 vPos[4];
	vPos[0] = D3DXVECTOR3(NowX * 10.0f, Height[NowX][NowZ], NowZ * 10.0f);
	vPos[1] = D3DXVECTOR3(NowX * 10.0f, Height[NowX][NowZ + 1], (NowZ + 1) * 10.0f);
	vPos[2] = D3DXVECTOR3((NowX + 1) * 10.0f, Height[NowX + 1][NowZ + 1], (NowZ + 1) * 10.0f);
	vPos[3] = D3DXVECTOR3((NowX + 1) * 10.0f, Height[NowX + 1][NowZ], NowZ * 10.0f);

	//ここからレイ判定
	float Dis;
	if (D3DXIntersectTri(&vPos[0], &vPos[1], &vPos[2], &Pos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis) ||
		D3DXIntersectTri(&vPos[0], &vPos[2], &vPos[3], &Pos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis))
	{
	}
	return Dis;
}
