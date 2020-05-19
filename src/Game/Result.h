#pragma once
#include"../System/FrameBase/GameObject.h"


class Result:GameObject
{
public:
	Result();
	~Result();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex = nullptr;//É{Å[Éh
	KdMatrix mMat;
	D3DXVECTOR3 mPos;

};

