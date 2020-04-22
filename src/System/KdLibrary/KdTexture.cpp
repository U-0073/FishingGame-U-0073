#include"KdLibrary.h"
#include"KdTexture.h"

bool KdTexture::Load(const std::string& filename)
{
	Release();

	HRESULT hr;

	hr = D3DXCreateTextureFromFileEx(KD3D.GetDev(),
		filename.c_str(),		// ファイル名
		D3DX_DEFAULT_NONPOW2,	// 幅をそのまま読み込む
		D3DX_DEFAULT_NONPOW2,	// 高さをそのまま読み込む
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&m_info,				// ここの画像情報が入る
		nullptr,
		&m_tex					// ここの読み込んだテクスチャが入る
	);

	if (FAILED(hr))
	{
		return false;
	}

	// Rectを生成しておく
	SetRect(&m_rc, 0, 0, m_info.Width, m_info.Height);

	return true;
}
