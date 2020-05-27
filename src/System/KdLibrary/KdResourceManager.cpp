#include"../KdLibrary/KdLibrary.h"
#include"KdResourceManager.h"

std::shared_ptr<KdModel> KdResourcemanager::GetModel(const std::string& Filename)
{
	std::string Path = "Resource/3DModel/";
	std::string Format = ".x";
	Path = Path + Filename + Format;
	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_models.find(Path) != m_models.end()) {
		//���ɂ�����
		return m_models[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}


	//�܂��Ȃ�����
	auto nModel = std::make_shared<KdModel>();
	if (nModel->LoadXFile(Path) == false) {

		//�ǂݍ��߂Ȃ�����
		nModel = nullptr;
		return nullptr;
	}
	//���X�g�ɒǉ�
	m_models[Path] = nModel;

	return nModel;
}
//Flyweight�p�^�[��
//���\�[�X�̊Ǘ����ꌳ�����A
//�K�v�ȏꏊ�Ŏg���܂킷�p�^�[��

std::shared_ptr < LPDIRECT3DTEXTURE9 >KdResourcemanager::GetTexture(const std::string& Filename, int W, int H, const D3DCOLOR Color)
{
	std::string Path = "Resource/Texture/";
	Path = Path + Filename;

	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Path) != m_texture.end()) {
		//���ɂ�����
		return m_texture[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}

	//�܂��Ȃ�����
	auto nTexture = std::make_shared< LPDIRECT3DTEXTURE9>();
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	KD3D.LoadTexture(&(*nTexture), Path, W, H, Color);

	if (nTexture == nullptr) {

		//�ǂݍ��߂Ȃ�����

		return nullptr;
	}
	//���X�g�ɒǉ�
	m_texture[Path] = nTexture;

	return m_texture[Path];

}
std::shared_ptr < LPDIRECT3DTEXTURE9 >KdResourcemanager::GetTexture(const std::string& Filename, const D3DCOLOR Color)
{
	std::string Path = "Resource/Texture/";
	Path = Path + Filename;

	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Path) != m_texture.end()) {
		//���ɂ�����
		return m_texture[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}

	//�܂��Ȃ�����
	auto nTexture = std::make_shared< LPDIRECT3DTEXTURE9>();
	KD3D.LoadTexture(&(*nTexture), Path, Color);

	if (nTexture == nullptr) {

		//�ǂݍ��߂Ȃ�����

		return nullptr;
	}
	//���X�g�ɒǉ�
	m_texture[Path] = nTexture;

	return m_texture[Path];

}
std::shared_ptr < LPDIRECT3DTEXTURE9 >KdResourcemanager::GetTexture(const std::string& Filename)
{
	std::string Path = "Resource/Texture/";
	Path = Path + Filename;

	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Path) != m_texture.end()) {
		//���ɂ�����
		return m_texture[Path];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}

	//�܂��Ȃ�����
	auto nTexture = std::make_shared< LPDIRECT3DTEXTURE9>();
	KD3D.LoadTexture(&(*nTexture), Path);

	if (nTexture == nullptr) {

		//�ǂݍ��߂Ȃ�����

		return nullptr;
	}
	//���X�g�ɒǉ�
	m_texture[Path] = nTexture;

	return m_texture[Path];
}
std::shared_ptr < LPDIRECT3DTEXTURE9 >KdResourcemanager::GetModelTexture(const std::string& Filename)
{
	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_texture.find(Filename) != m_texture.end()) {
		//���ɂ�����
		return m_texture[Filename];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}

	//�܂��Ȃ�����
	auto nTexture = std::make_shared< LPDIRECT3DTEXTURE9>();
	KD3D.LoadTexture(&(*nTexture), Filename);

	if (nTexture == nullptr) {

		//�ǂݍ��߂Ȃ�����

		return nullptr;
	}
	//���X�g�ɒǉ�
	m_texture[Filename] = nTexture;

	return m_texture[Filename];
}

std::shared_ptr<SoundBase> KdResourcemanager::GetSound(const std::string& Filename)
{
	std::string Path = "Resource/Sound/";
	std::string Format = ".wav";
	Path = Path + Filename + Format;

	if (m_sounds.find(Path) != m_sounds.end()) {
		//���ɂ�������
		return m_sounds[Path];
	}
	//�܂����݂��Ȃ�����
	auto nSound = std::make_shared<SoundBase>();
	nSound->SetPos(D3DXVECTOR3(10, 10, 10));

	if (nSound->Loadsound(Path.c_str()) == false) {
		//�ǂݍ��߂Ȃ�����
		nSound = nullptr;
		return nullptr;
	}
	//���X�g�ɒǉ�
	m_sounds.emplace(Path, nSound);
	return nSound;
}
