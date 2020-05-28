#pragma once
#include"../System/FrameBase/GameObject.h"



class Title : GameObject
{
public:
	Title();
	~Title();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void End()override;

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex = nullptr;


	KdMatrix mMat;//�^�C�g��
	KdVec3 mPos;

	KdMatrix mMat2;//�G���^�[�L�[
	KdVec3 mPos2;
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex2 = nullptr;
	int alpha;


};

