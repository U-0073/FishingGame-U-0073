#pragma once

class KdModel;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(const std::string&Filename);//リソースの管理
	void clear(void) { m_models.clear(); m_texture.clear(); }

	LPDIRECT3DTEXTURE9 GetTexture( const std::string& Path, const int W, const int H, const D3DCOLOR Color);

private:

	//モデルデータ
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//テクスチャ
	std::map<std::string, LPDIRECT3DTEXTURE9>m_texture;
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