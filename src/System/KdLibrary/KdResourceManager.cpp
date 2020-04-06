#include"../KdLibrary/KdLibrary.h"
#include"KdResourceManager.h"

std::shared_ptr<KdModel> KdResourcemanager::GetModel(LPDIRECT3DDEVICE9& mpD3DDevice,const std::string & Filename)
{
	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_models.find(Filename) != m_models.end()) {
		//���ɂ�����
		return m_models[Filename];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}


	//�܂��Ȃ�����
	auto nModel = std::make_shared<KdModel>();
	if (nModel->LoadXFile(mpD3DDevice,Filename) == false) {
	
		//�ǂݍ��߂Ȃ�����
		nModel = nullptr;
		return nullptr;
	}
	//���X�g�ɒǉ�
	m_models[Filename] = nModel;

	return nModel;
}
//Flyweight�p�^�[��
//���\�[�X�̊Ǘ����ꌳ�����A
//�K�v�ȏꏊ�Ŏg���܂킷�p�^�[��