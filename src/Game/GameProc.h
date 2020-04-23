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
	//å≈íËòg
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;
	float scale;
	//ÉmÅ[Éc
	KdMatrix notesMat;
	//îªíËï∂éö
	LPDIRECT3DTEXTURE9 JudgeTex;
};