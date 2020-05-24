#pragma once
#include"../../System/FrameBase/CSceneBase.h"

class Shop2D;
class ShopObject;

class CShopScene : public CSceneBase
{
public:
	CShopScene();
	~CShopScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return SHOP; };
	void End()override;

private:
	std::shared_ptr<Shop2D> shop2d = nullptr;
	std::shared_ptr<ShopObject> shopObj = nullptr;


	KdMatrix mMat;
	KdMatrix mScale;
	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex;


	std::shared_ptr<SoundBase> m_pSound = nullptr;

	//èäéùã‡
	int Possession;

};