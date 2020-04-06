#pragma once
#include"../System/FrameBase/GameObject.h"

class TestCharacter : GameObject
{
public:
	TestCharacter();
	~TestCharacter();

	void Init()override;
	void Update()override;
	void Draw3D()override;
private:

};