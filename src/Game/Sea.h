#pragma once


// í∏ì_èÓïÒÇÃíËã`
struct VERTEX
{
	KdVec3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};

class Sea 
{
public:
	Sea();
	~Sea();

	void   Init();
	void Update();
	void Draw2D();
	void Draw3D();
	void    End();

private:
	KdVec3 mSize = { 1000,0,1000 };
	KdVec3 mPos = { 0,-3,25 };
	KdMatrix m_world;
	float vScale;

	VERTEX v[4];
	VERTEX v2[4];

	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex = nullptr;

	float speed=0.01f;
};