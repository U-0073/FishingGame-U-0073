#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{
	

	srand(timeGetTime());
	m_pModel = RESOURCE_MNG.GetModel("Resource/3DModel/Sea.x");

	verNum = MESH->GetNumVertices();

	for (DWORD i = 0; i < verNum; i++) {
		CLONEVERTEX* pV;

		MESH->LockVertexBuffer(0, (LPVOID*)&pV);
		//�N���[��			���_�o�b�t�@				�擪�A�h���X������(0�Ԗڂ̒��_�̓��e)

		
	}
	MESH->UnlockVertexBuffer();

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
