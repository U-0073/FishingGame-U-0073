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
	KdMatrix notesMat;
	//���蕶��
	LPDIRECT3DTEXTURE9 JudgeTex;
};