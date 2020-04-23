#include "KdLibrary.h"
#include "KdModel.h"

bool KdModel::LoadXFile(const std::string& filename)
{
	Release();

	// �p�X�A�t�@�C��������
	std::string Path;
	char szDir[_MAX_PATH];	// �t�H���_
	char szFname[_MAX_FNAME];	// �t�@�C����(�g���q������)
	char szExt[_MAX_EXT];		// �g���q
	_splitpath_s(filename.c_str(),
		nullptr, 0,
		szDir, sizeof(szDir),
		szFname, sizeof(szFname),
		szExt, sizeof(szExt));
	Path = szDir;

	// �t�@�C�����L��
	m_fileName = szFname;
	m_fileName += szExt;

	// X�t�@�C���ǂݍ���
	HRESULT hr;
	LPD3DXBUFFER	pD3DXMtrlBuffer;
	DWORD mateNum;
	hr = D3DXLoadMeshFromX(filename.c_str(),
		D3DXMESH_SYSTEMMEM,
		KD3D.GetDev(),
		nullptr,
		&pD3DXMtrlBuffer,	// �}�e���A���f�[�^���i�[���邽�߂̕ϐ����w��
		nullptr,
		&mateNum,			// �}�e���A�������i�[���邽�߂̕ϐ����w��
		&m_pMesh);			// ���b�V���f�[�^���i�[���邽�߂̕ϐ����w��
	if (FAILED(hr)) {
		return false;
	}


	// ���b�V���̃}�e���A���̑����Ɋ�Â��āA�}�e���A���z����쐬
	m_materials.resize(mateNum);

	// pD3DXMtrlBuffer ����A������e�N�X�`���[�̏���ǂݎ��
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	// �}�e���A���R�s�[�A�e�N�X�`���ǂݍ���
	std::string strTexFile;
	for (DWORD i=0; i<mateNum; i++) {
		// �ގ�
		m_materials[i].matD3D = d3dxMaterials[i].MatD3D;			// �����̃R�s�[
		m_materials[i].matD3D.Ambient = m_materials[i].matD3D.Diffuse;	// Ambient��Diffuse�̃R�s�[���g�p

																		// �e�N�X�`���� Path + �t�@�C����
		strTexFile = Path;
		if (d3dxMaterials[i].pTextureFilename) { strTexFile += d3dxMaterials[i].pTextureFilename; }

		// �e�N�X�`���ǂݍ���
		/*
		D3DXIMAGE_INFO		m_Info;			
		HRESULT hr = D3DXCreateTextureFromFileEx(
			KD3D.GetDev(),
			strTexFile.c_str(),
			D3DX_DEFAULT_NONPOW2,			
			D3DX_DEFAULT_NONPOW2,			
			D3DX_DEFAULT,					
			0,								
			D3DFMT_UNKNOWN,					
			D3DPOOL_DEFAULT,				
			D3DX_DEFAULT,					
			D3DX_DEFAULT,					
			0,								 
			&m_Info,						
			nullptr,						
			&m_materials[i].pTex);			
		*/

		m_materials[i].pTex = *RESOURCE_MNG.GetTexture(strTexFile.c_str());
	}

	// ��Ɨp�}�e���A�� �o�b�t�@�J��
	KdSafeRelease(pD3DXMtrlBuffer);

	return true;
}

void KdModel::Release()
{
	// ���b�V�����
	KdSafeRelease(m_pMesh);

	// �}�e���A�����
	for(UINT i=0;i<m_materials.size();i++){
		KdSafeRelease(m_materials[i].pTex);
	}
	m_materials.clear();

	// �t�@�C����
	m_fileName = "";
}

void KdModel::Draw()
{
	// ���b�V�����Ȃ��Ƃ��́A�������Ȃ�
	if(m_pMesh == nullptr)return;

	// �}�e���A���P�ʂŕ`�悷��
	for(UINT i=0;i<m_materials.size();i++){
		// i�Ԗڂ̃}�e���A��(�ގ����)���Z�b�g
		KD3D.GetDev()->SetMaterial(&m_materials[i].matD3D);
		// i�Ԗڂ̃e�N�X�`��(�摜)���Z�b�g
		KD3D.GetDev()->SetTexture(0, m_materials[i].pTex);

		// i�Ԗڂ̃}�e���A���̃|���S����`��
		m_pMesh->DrawSubset(i);
	}
}
