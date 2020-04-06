#pragma once

class KdModel;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(const std::string&Filename);//���\�[�X�̊Ǘ�
	void clear(void) { m_models.clear(); m_texture.clear(); }

	LPDIRECT3DTEXTURE9 GetTexture( const std::string& Path, const int W, const int H, const D3DCOLOR Color);

private:

	//���f���f�[�^
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//�e�N�X�`��
	std::map<std::string, LPDIRECT3DTEXTURE9>m_texture;
	//�T�E���h�f�[�^

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