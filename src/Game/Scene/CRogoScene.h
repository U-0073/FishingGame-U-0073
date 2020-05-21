#pragma once
#include"../../System/FrameBase/CSceneBase.h"

class CSceneBase;

class CRogoScene : public CSceneBase
{
public:


	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override {};

	int GetID()override { return ROGO; };

	void End()override;


private:
	//anime
	std::shared_ptr<LPDIRECT3DTEXTURE9> titleAnime = nullptr;
	std::shared_ptr<LPDIRECT3DTEXTURE9> whiteAnime = nullptr;
	KdMatrix animMat;
	KdMatrix wAnim;
	int animAlpha;
	bool animFlg;

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};