#pragma once
#include"../System/FrameBase/CSceneBase.h"
#define path "Resouce/Texture/"
#include"Title.h"
#include"Skysphere.h"
#include"Fish.h"
#include"Sea.h"

class Skysphere;
class Fish;
class Title;
class Sea;

class CTitleScene : public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void CTitleScene::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string Path, int W, int H, const D3DCOLOR Color);


private:
	std::shared_ptr<Skysphere> Sky = nullptr;
	std::shared_ptr<Fish> Fishes = nullptr;
	std::shared_ptr<Title> title = nullptr;
	std::shared_ptr<Sea> sea = nullptr;
	
	D3DXVECTOR3 mPos=D3DXVECTOR3(0,0,0);



};