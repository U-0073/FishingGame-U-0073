#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{
}

Sea::~Sea()
{
}


void Sea::Init()
{
	vTex = RESOURCE_MNG.GetTexture("Sea.png");

	//板ポリの中心点が対角線の交点になるように配置している
	v2[0].Pos = v[0].Pos = { -(mSize.x * 0.5f),  (mSize.y * 0.5f),  (mSize.z * 0.5f) };
	v2[1].Pos = v[1].Pos = { (mSize.x * 0.5f),  (mSize.y * 0.5f),  (mSize.z * 0.5f) };
	v2[2].Pos = v[2].Pos = { (mSize.x * 0.5f), -(mSize.y * 0.5f), -(mSize.z * 0.5f) };
	v2[3].Pos = v[3].Pos = { -(mSize.x * 0.5f), -(mSize.y * 0.5f), -(mSize.z * 0.5f) };


	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	v2[0].Color = D3DCOLOR_ARGB(150, 255, 255, 255);
	v2[1].Color = D3DCOLOR_ARGB(150, 255, 255, 255);
	v2[2].Color = D3DCOLOR_ARGB(150, 255, 255, 255);
	v2[3].Color = D3DCOLOR_ARGB(150, 255, 255, 255);

	vMax = 5.0f;
	vMin = 0.0f;

	//位置の設定
	m_world.SetTrans(mPos);
	mPos.y += 0.001f;
	m_world2.SetTrans(mPos);
	m_world2.SetRotation(0, 90, 0);
	DTWHOUCE.SetVec("Sea", m_world.GetPos());

}

void Sea::Update()
{
	vMin += speed;
	vMax += speed;
	if (vMin > 1.0f)vMin = 0.0f;
	if (vMax > 5.0f)vMax = 5.0f;
	//画像の設定
	v2[0].Tex = v[0].Tex = D3DXVECTOR2(vMin, vMin);
	v2[1].Tex = v[1].Tex = D3DXVECTOR2(vMax, vMin);
	v2[2].Tex = v[2].Tex = D3DXVECTOR2(vMax, vMax);
	v2[3].Tex = v[3].Tex = D3DXVECTOR2(vMin, vMax);

}

void Sea::Draw3D()
{
	D3DEV->SetFVF(FVF_VERTEX);
	D3DEV->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DEV->SetTexture(0, *vTex);
	KD3D.SetWorldMatrix(&m_world);
	D3DEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));

	KD3D.SetWorldMatrix(&m_world2);
	D3DEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v2, sizeof(VERTEX));
	D3DEV->SetTexture(0, NULL);

	D3DEV->SetRenderState(D3DRS_LIGHTING, TRUE);


}

void Sea::End()
{
	//m_pModel = nullptr;
}
