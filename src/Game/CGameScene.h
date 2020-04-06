#pragma once
#include"../System/FrameBase/CSceneBase.h"

//クラスの前方宣言
class TestCharacter;
class C_Player;		//プレイヤー全般


class Bord;
class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

private:
	std::shared_ptr<TestCharacter> test = nullptr;
	std::shared_ptr<Bord> Sea = nullptr;
	

	//林プログラム
	std::shared_ptr<C_Player> m_Player = nullptr;

};
