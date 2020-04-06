#pragma once

class KdModel{
public:
	// X�t�@�C���ǂݍ���
	// �Efilename	: �t�@�C����
	// �߂�l		: true �c ���� false �c ���s
	bool LoadXFile(const std::string& filename);

	// ���
	void Release();

	// �`��
	void Draw();

	// �f�X�g���N�^(���̃N���X��������Ƃ��ɁA�����Ŏ��s�����֐��ł�)
	~KdModel(){
		Release();
	}

private:
	// ���b�V��
	LPD3DXMESH	m_pMesh = nullptr;

	// �}�e���A���\����
	struct Material{
		D3DMATERIAL9 matD3D;		// �ގ�
		LPDIRECT3DTEXTURE9 pTex;	// �摜
	};

	std::vector<Material>	m_materials;

	// �t�@�C���� �L���p
	std::string		m_fileName;
};
