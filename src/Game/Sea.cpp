#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{
	

	srand(timeGetTime());
	m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Sea.x");

	auto verNum = (*m_pModel).GetMesh()->GetNumVertices();	
	CLONEVERTEX* pV;
(*m_pModel).GetMesh()->LockVertexBuffer(0, (LPVOID*)&pV);
	for (DWORD i = 0; i < verNum; i++) {


		
		//クローン			頂点バッファ				先頭アドレスが入る(0番目の頂点の内容)
	//	auto ad = *(pV + i);
		(pV + i)->Pos = D3DXVECTOR3(0, 0, 0);

	}
		(*m_pModel).GetMesh()->UnlockVertexBuffer();

	D3DXMatrixTranslation(&m_world, 0, -3, 0);

}

Sea::~Sea()
{
}


void Sea::Update()
{

}

void Sea::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
