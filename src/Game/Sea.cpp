#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{


	srand(timeGetTime());
	m_pModel = RESOURCE_MNG.GetModel("Sea");

	verNum = MESH->GetNumVertices();
	//移動量の設定
	D3DXMatrixTranslation(&m_world, 0, -3, 0);

	//
	int vSize = MESH->GetNumBytesPerVertex();

	//CLONEVERTEX* pV;
	pV = nullptr;

	MESH->LockVertexBuffer(0, (VOID**)&pV);
	/*
	//クローン			頂点バッファ				先頭アドレスが入る(0番目の頂点の内容)
	for (DWORD i = 0; i < verNum; i++) {
		D3DXVECTOR3* pos = (D3DXVECTOR3*)(pV + vSize * i);
		pos->y = (rand() % WaveHeight - WaveHeight / 2) * 0.01;
	}
	*/
	(*m_pModel).GetMesh()->UnlockVertexBuffer();

	HeightCtrl = false;
}

Sea::~Sea()
{
}


void Sea::Update()
{
	int vSize = MESH->GetNumBytesPerVertex();
	pV = nullptr;

	MESH->LockVertexBuffer(0, (VOID**)&pV);
	//クローン			頂点バッファ				先頭アドレスが入る(0番目の頂点の内容)

	/*
	for (DWORD i = 0; i < verNum; i++) {
		D3DXVECTOR3* pos = (D3DXVECTOR3*)(pV + vSize * i);
		if (HeightCtrl == false) {
			pos->y += 0.02;
			if (pos->y > 1) { HeightCtrl = true; }
		}
		else {
			pos->y -= 0.02;
			if (pos->y < -1) { HeightCtrl = false; }
		}
	}

	*/
	MESH->UnlockVertexBuffer();
}

void Sea::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void Sea::End()
{
	//m_pModel = nullptr;
}
