#pragma once

class KdModel;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(LPDIRECT3DDEVICE9& mpD3DDevice,const std::string&Filename);//リソースの管理
	void clear(void) { m_models.clear(); }
private:

	//モデルデータ
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//テクスチャ

	//サウンドデータ

private:
	KdResourcemanager() {} // ← コンストラクタ
	~KdResourcemanager() {} // ←デストラクタ

public:
	static KdResourcemanager& GetInstance()
	{
		static KdResourcemanager instance;
		return instance;

	}
};
#define RESOURCE_MNG KdResourcemanager::GetInstance()