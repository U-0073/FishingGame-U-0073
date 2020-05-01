#pragma once

class CGameProc
{
public:
	CGameProc();
	~CGameProc();
	void Init();
	void Update();
	void Draw();
	void End();

private:
	//�Œ�g
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;
	float scale;
	//�m�[�c
	LPDIRECT3DTEXTURE9 notesTex;
	KdMatrix notesMat;
	//���蕶��
	LPDIRECT3DTEXTURE9 judgeTex;
	KdMatrix judgeMat;
	//�����ނ��܂ł̋���
	float dist;
	int level;
	float speed;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	int wait;

	std::vector<std::shared_ptr<SoundBase>> m_pSound;
};