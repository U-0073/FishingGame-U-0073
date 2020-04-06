#include"../KdLibrary/KdLibrary.h"
#include"KdResourceManager.h"

std::shared_ptr<KdModel> KdResourcemanager::GetModel(const std::string & Filename)
{
	//既に読み込んだかどうかを調べる
	if (m_models.find(Filename) != m_models.end()) {
		//既にあった
		return m_models[Filename];
		//↑指定したキーにつながっている要素にアクセス
		//存在しないキーを使った場合、自動追加してしまう
	}


	//まだなかった
	auto nModel = std::make_shared<KdModel>();
	if (nModel->LoadXFile(Filename) == false) {
	
		//読み込めなかった
		nModel = nullptr;
		return nullptr;
	}
	//リストに追加
	m_models[Filename] = nModel;

	return nModel;
}
//Flyweightパターン
//リソースの管理を一元化し、
//必要な場所で使いまわすパターン

LPDIRECT3DTEXTURE9 KdResourcemanager::GetTexture(const std::string& Path, int W, int H, const D3DCOLOR Color)
{
	//既に読み込んだかどうかを調べる
	if (m_texture.find(Path) != m_texture.end()) {
		//既にあった
		return m_texture[Path];
		//↑指定したキーにつながっている要素にアクセス
		//存在しないキーを使った場合、自動追加してしまう
	}


	//まだなかった
	LPDIRECT3DTEXTURE9 nTexture;
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(KD3D.GetDev(), Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, &nTexture);

	if (nTexture = nullptr) {

		//読み込めなかった
	
		return nullptr;
	}
	//リストに追加
	m_texture[Path] = nTexture;

	return nTexture;






}