#pragma once

class CGameProc
{
	CGameProc();
	~CGameProc();
	void Init();
	void Update();
	void Draw();
	void End();

private:
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;
	LPDIRECT3DTEXTURE9 notesTex;

	LPDIRECT3DTEXTURE9 JudgeTex;
};