#pragma once
#include"../System/FrameBase/CSceneBase.h"

//�N���X�̑O���錾
class Skysphere;
class Port;
class Fish;
class C_Player;		//�v���C���[�S��
class C_Fishing;

class Sea;

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;
	void CGameScene::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string Path, int W, int H, const D3DCOLOR Color);

private:
	std::shared_ptr<Skysphere> Sky = nullptr;
	std::shared_ptr<Sea> Seas = nullptr;
	std::shared_ptr<Port> m_Port = nullptr;
	//std::shared_ptr<Fish> Fishes = nullptr;
	std::shared_ptr<C_Fishing> m_Fishing = nullptr;
	
	LPDIRECT3DTEXTURE9 seaTex;

	//�уv���O����
	std::shared_ptr<C_Player> m_Player = nullptr;
};
