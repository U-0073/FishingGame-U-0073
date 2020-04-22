#pragma once


class KdTexture
{
public:
	bool Load(const std::string& filename);

	void Release() { KdSafeRelease(m_tex); }

	~KdTexture() { Release(); }

private:
	// Direct3D�̃e�N�X�`��
	LPDIRECT3DTEXTURE9	m_tex = nullptr;

	// �摜���
	D3DXIMAGE_INFO		m_info;
	RECT m_rc; // �e�N�X�`���̋�`

	// �T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_lpSur = nullptr;

};