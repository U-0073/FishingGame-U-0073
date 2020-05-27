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
	v[0].Pos = { -(mSize.x * 0.5f),  (mSize.y * 0.5f),  (mSize.z * 0.5f) };
	v[1].Pos = {  (mSize.x * 0.5f),  (mSize.y * 0.5f),  (mSize.z * 0.5f) };
	v[2].Pos = {  (mSize.x * 0.5f), -(mSize.y * 0.5f), -(mSize.z * 0.5f) };
	v[3].Pos = { -(mSize.x * 0.5f), -(mSize.y * 0.5f), -(mSize.z * 0.5f) };


	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	vScale = 5.0f;

	//位置の設定
	m_world.SetTrans(mPos);
	DTWHOUCE.SetVec("Sea", m_world.GetPos());
}

void Sea::Update()
{
	//画像の設定
	v[0].Tex = D3DXVECTOR2(0,		0);
	v[1].Tex = D3DXVECTOR2(vScale,	0);
	v[2].Tex = D3DXVECTOR2(vScale,	vScale);
	v[3].Tex = D3DXVECTOR2(0,		vScale);
}

void Sea::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);
	D3DEV->SetFVF(FVF_VERTEX);
	D3DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DEV->SetTexture(0, *vTex);
	D3DEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
	D3DEV->SetTexture(0, NULL);
	D3DEV->SetRenderState(D3DRS_LIGHTING, TRUE);


}

void Sea::End()
{
	//m_pModel = nullptr;
}
