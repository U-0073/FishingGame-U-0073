#include"../System/KdLibrary/KdLibrary.h"
#include"Sea.h"

Sea::Sea()
{


	srand(timeGetTime());
	m_pModel = RESOURCE_MNG.GetModel("Resource/3DModel/Sea.x");

	verNum = MESH->GetNumVertices();
	//�ړ��ʂ̐ݒ�
	D3DXMatrixTranslation(&m_world, 0, -3, 0);

}

Sea::~Sea()
{
}


void Sea::Update()
{
	for (DWORD i = 0; i < verNum; i++) {
		//CLONEVERTEX* pV;
		D3DXVECTOR3* pV = nullptr;

		MESH->LockVertexBuffer(0, (VOID**)&pV);
		//�N���[��			���_�o�b�t�@				�擪�A�h���X������(0�Ԗڂ̒��_�̓��e)

		(pV + i)->y += (rand() % 4 - 2) * 0.01;
		MESH->UnlockVertexBuffer();
	}
}

void Sea::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

}
