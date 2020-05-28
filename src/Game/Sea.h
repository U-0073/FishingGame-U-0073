#pragma once



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
	KdVec3 mPos = { 0.0f,-3.0f,25.0f };
	KdMatrix m_world;
	KdMatrix m_world2;
	float vMin;
	float vMax;

	VERTEX v[4];
	VERTEX v2[4];

	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex = nullptr;

	float speed=0.0001f;
};