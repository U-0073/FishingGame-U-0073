#include"../KdLibrary/KdLibrary.h"
#include"KdResourceManager.h"

std::shared_ptr<KdModel> KdResourcemanager::GetModel(const std::string & Filename)
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
	if (nModel->LoadXFile(Filename) == false) {
	
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

const LPDIRECT3DTEXTURE9 KdResourcemanager::GetTexture(const std::string& Path, int W, int H, const D3DCOLOR Color)
{
	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Path) != m_texture.end()) {
		//���ɂ�����
		return m_texture[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}


	//�܂��Ȃ�����
	LPDIRECT3DTEXTURE9 nTexture;
	//auto nTexture = std::make_shared<LPDIRECT3DTEXTURE9>();
	//if (W == 0)W = D3DX_DEFAULT;
	//if (H == 0)H = D3DX_DEFAULT;
	//KD3D.LoadTexture(&nTexture,Path, W, H, Color);
	//D3DXCreateTextureFromFileEx(KD3D.GetDev(), Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, &nTexture);

	if (nTexture == nullptr) {

		//�ǂݍ��߂Ȃ�����
	
		return nullptr;
	}
	//���X�g�ɒǉ�
	m_texture[Path] = nTexture;

	return m_texture[Path];






}

void KdResourcemanager::GetTexture(LPDIRECT3DTEXTURE9& lpTex, const std::string& Path, int W,  int H, const D3DCOLOR Color)
{

	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Path) != m_texture.end()) {
		//���ɂ�����
		lpTex = m_texture[Path];
		//return m_texture[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}


	//�܂��Ȃ�����
	LPDIRECT3DTEXTURE9 nTexture;
	//auto nTexture = std::make_shared<LPDIRECT3DTEXTURE9>();
	//if (W == 0)W = D3DX_DEFAULT;
	//if (H == 0)H = D3DX_DEFAULT;
	//KD3D.LoadTexture(&lpTex,Path, W, H, Color);
	//D3DXCreateTextureFromFileEx(KD3D.GetDev(), Path.c_str(), W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, &nTexture);

	//if (nTextur == nullptr) {

	//	//�ǂݍ��߂Ȃ�����

	//	return nullptr;
	//}
	//���X�g�ɒǉ�
	m_texture[Path] = lpTex;

	if (lpTex == nullptr);
	//return m_texture[Path];
}

std::shared_ptr<SoundBase> KdResourcemanager::GetSound(const std::string& Path)
{
	if (m_sounds.find(Path) != m_sounds.end()) {
		//���ɂ�����
		return m_sounds[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}
	//�܂����݂��Ȃ�����
	auto nSound = std::make_shared<SoundBase>();
	if (nSound->LoadSound(&Path) == false) {
		//�ǂݍ��߂Ȃ�����
		nSound = nullptr;
		return nullptr;
	}
	//���X�g�ɒǉ�
	m_sounds[Path] = nSound;

	return nSound;
}