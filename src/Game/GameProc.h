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
	//ŒÅ’è˜g
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;
	float scale;
	//ƒm[ƒc
	KdMatrix notesMat;
	//”»’è•¶š
	LPDIRECT3DTEXTURE9 JudgeTex;
	//‹›‚ª’Ş‚ê‚é‚Ü‚Å‚Ì‹——£
	float dist;
	int level;
	int size;
};