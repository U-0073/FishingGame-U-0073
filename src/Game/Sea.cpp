#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{


	srand(timeGetTime());
	m_pModel = RESOURCE_MNG.GetModel("Resource/3DModel/Sea.x");

	verNum = MESH->GetNumVertices();
	//移動量の設定
	D3DXMatrixTranslation(&m_world, 0, -3, 0);


	//CLONEVERTEX* pV;
	pV = nullptr;

	MESH->LockVertexBuffer(0, (VOID**)&pV);
	//クローン			頂点バッファ				先頭アドレスが入る(0番目の頂点の内容)
	for (DWORD i = 0; i < verNum; i++) {
		(pV + i)->y = (rand() % WaveHeight - WaveHeight / 2) * 0.01;
	}
		(*m_pModel).GetMesh()->UnlockVertexBuffer();

	HeightCtrl = false;
}

Sea::~Sea()
{
	m_pModel = nullptr;
}


void Sea::Update()
{

	MESH->LockVertexBuffer(0, (VOID**)&pV);
	//クローン			頂点バッファ				先頭アドレスが入る(0番目の頂点の内容)


	for (DWORD i = 0; i < verNum; i++) {
		if (HeightCtrl == false) {
			(pV + i)->y += 0.002;
			if ((pV + i)->y > 1) { HeightCtrl = true; }
		}
		else {
			(pV + i)->y -= 0.002;
			if ((pV + i)->y < -1) { HeightCtrl = false; }
		}
	}
	MESH->UnlockVertexBuffer();

}

void Sea::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
