#pragma once
#include"../System/FrameBase/CSceneBase.h"

class TestCharacter;
class Board;
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
	std::shared_ptr<Board> Sea = nullptr;
	

};
