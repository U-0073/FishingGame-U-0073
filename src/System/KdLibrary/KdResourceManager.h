#pragma once

class KdModel;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(LPDIRECT3DDEVICE9& mpD3DDevice,const std::string&Filename);//���\�[�X�̊Ǘ�
	void clear(void) { m_models.clear(); }
private:

	//���f���f�[�^
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//�e�N�X�`��

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