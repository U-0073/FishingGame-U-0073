#pragma once
#include"../../System/FrameBase/CSceneBase.h"

//クラスの前方宣言
class Skysphere;
class Port;
class Fish;
class C_Player;		//プレイヤー全般
class C_Fishing;
class Seagull;
class CShopObject;

class Sea;

class CMapScene : public CSceneBase
{
public:
	CMapScene();
	~CMapScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;

	int GetID()override { return MAP; };
	void End()override;

private:
	std::shared_ptr<Skysphere> Sky = nullptr;
	std::shared_ptr<Sea> Seas = nullptr;
	std::shared_ptr<Port> m_Port = nullptr;
	std::shared_ptr<C_Fishing> m_Fishing = nullptr;
	std::shared_ptr<C_Player> m_Player = nullptr;
	std::shared_ptr<Seagull> m_Seagull = nullptr;



	std::shared_ptr<SoundBase> m_PSound = nullptr;
	std::shared_ptr<SoundBase> m_PBGM = nullptr;

};
