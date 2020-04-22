#pragma once


class KdTexture
{
public:
	bool Load(const std::string& filename);

	void Release() { KdSafeRelease(m_tex); }

	~KdTexture() { Release(); }

private:
	// Direct3Dのテクスチャ
	LPDIRECT3DTEXTURE9	m_tex = nullptr;

	// 画像情報
	D3DXIMAGE_INFO		m_info;
	RECT m_rc; // テクスチャの矩形

	// サーフェイス
	LPDIRECT3DSURFACE9 m_lpSur = nullptr;

};