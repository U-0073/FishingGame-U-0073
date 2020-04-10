#pragma once

class KdModel;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(const std::string& Filename);//���\�[�X�̊Ǘ�
	void clear(void) { m_models.clear(); m_texture.clear(); }

	//void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string& Path, int W, int H, const D3DCOLOR Color)
	//{
	//	if (W == 0)W = D3DX_DEFAULT;
	//	if (H == 0)H = D3DX_DEFAULT;
	//	D3DXCreateTextureFromFileEx(KD3D.GetDev(), Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);

	//}

	const LPDIRECT3DTEXTURE9 GetTexture(const std::string& Path, int W, int H, const D3DCOLOR Color);
	void GetTexture(LPDIRECT3DTEXTURE9& lpTex, const std::string& Path, const int W, const int H, const D3DCOLOR Color);
//���̓Ǎ�
	void LoadSound(std::string fname);

private:

	//���f���f�[�^
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//�e�N�X�`��
	std::map<std::string, LPDIRECT3DTEXTURE9>m_texture;
	//�T�E���h�f�[�^
	struct SoundData
	{
		LPDIRECTSOUND3DBUFFER8	LDS3B8;
		LPDIRECTSOUNDBUFFER8	LDSB8;
		D3DXVECTOR3 SEPos;
	};


	std::map<std::string, std::shared_ptr<SoundData>> m_Sound;
private:
	KdResourcemanager() {} // �� �R���X�g���N�^
	~KdResourcemanager() {} // ���f�X�g���N�^

public:
	static KdResourcemanager& GetInstance()
	{
		static KdResourcemanager instance;
		return instance;

	}
};
#define RESOURCE_MNG KdResourcemanager::GetInstance()