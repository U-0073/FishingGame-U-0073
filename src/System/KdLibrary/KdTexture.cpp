#include"KdLibrary.h"
#include"KdTexture.h"

bool KdTexture::Load(const std::string& filename)
{
	Release();

	HRESULT hr;

	hr = D3DXCreateTextureFromFileEx(KD3D.GetDev(),
		filename.c_str(),		// �t�@�C����
		D3DX_DEFAULT_NONPOW2,	// �������̂܂ܓǂݍ���
		D3DX_DEFAULT_NONPOW2,	// ���������̂܂ܓǂݍ���
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&m_info,				// �����̉摜��񂪓���
		nullptr,
		&m_tex					// �����̓ǂݍ��񂾃e�N�X�`��������
	);

	if (FAILED(hr))
	{
		return false;
	}

	// Rect�𐶐����Ă���
	SetRect(&m_rc, 0, 0, m_info.Width, m_info.Height);

	return true;
}
