#include"../KdLibrary/KdLibrary.h"
#include"KdResourceManager.h"

std::shared_ptr<KdModel> KdResourcemanager::GetModel(LPDIRECT3DDEVICE9& mpD3DDevice,const std::string & Filename)
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
	if (nModel->LoadXFile(mpD3DDevice,Filename) == false) {
	
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