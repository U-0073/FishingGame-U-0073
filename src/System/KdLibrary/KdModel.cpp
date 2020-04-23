#include "KdLibrary.h"
#include "KdModel.h"

bool KdModel::LoadXFile(const std::string& filename)
{
	Release();

	// パス、ファイル名分解
	std::string Path;
	char szDir[_MAX_PATH];	// フォルダ
	char szFname[_MAX_FNAME];	// ファイル名(拡張子を除く)
	char szExt[_MAX_EXT];		// 拡張子
	_splitpath_s(filename.c_str(),
		nullptr, 0,
		szDir, sizeof(szDir),
		szFname, sizeof(szFname),
		szExt, sizeof(szExt));
	Path = szDir;

	// ファイル名記憶
	m_fileName = szFname;
	m_fileName += szExt;

	// Xファイル読み込み
	HRESULT hr;
	LPD3DXBUFFER	pD3DXMtrlBuffer;
	DWORD mateNum;
	hr = D3DXLoadMeshFromX(filename.c_str(),
		D3DXMESH_SYSTEMMEM,
		KD3D.GetDev(),
		nullptr,
		&pD3DXMtrlBuffer,	// マテリアルデータを格納するための変数を指定
		nullptr,
		&mateNum,			// マテリアル数を格納するための変数を指定
		&m_pMesh);			// メッシュデータを格納するための変数を指定
	if (FAILED(hr)) {
		return false;
	}


	// メッシュのマテリアルの総数に基づいて、マテリアル配列を作成
	m_materials.resize(mateNum);

	// pD3DXMtrlBuffer から、質感やテクスチャーの情報を読み取る
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	// マテリアルコピー、テクスチャ読み込み
	std::string strTexFile;
	for (DWORD i=0; i<mateNum; i++) {
		// 材質
		m_materials[i].matD3D = d3dxMaterials[i].MatD3D;			// 質感のコピー
		m_materials[i].matD3D.Ambient = m_materials[i].matD3D.Diffuse;	// AmbientはDiffuseのコピーを使用

																		// テクスチャ名 Path + ファイル名
		strTexFile = Path;
		if (d3dxMaterials[i].pTextureFilename) { strTexFile += d3dxMaterials[i].pTextureFilename; }

		// テクスチャ読み込み
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

	// 作業用マテリアル バッファ開放
	KdSafeRelease(pD3DXMtrlBuffer);

	return true;
}

void KdModel::Release()
{
	// メッシュ解放
	KdSafeRelease(m_pMesh);

	// マテリアル解放
	for(UINT i=0;i<m_materials.size();i++){
		KdSafeRelease(m_materials[i].pTex);
	}
	m_materials.clear();

	// ファイル名
	m_fileName = "";
}

void KdModel::Draw()
{
	// メッシュがないときは、何もしない
	if(m_pMesh == nullptr)return;

	// マテリアル単位で描画する
	for(UINT i=0;i<m_materials.size();i++){
		// i番目のマテリアル(材質情報)をセット
		KD3D.GetDev()->SetMaterial(&m_materials[i].matD3D);
		// i番目のテクスチャ(画像)をセット
		KD3D.GetDev()->SetTexture(0, m_materials[i].pTex);

		// i番目のマテリアルのポリゴンを描画
		m_pMesh->DrawSubset(i);
	}
}
