#pragma once
#include"../System/FrameBase/GameObject.h"

class Port : GameObject
{
public:
	Port();
	~Port();
	
	void Init()override;
	void Update()override;
	void Draw3D()override;
	void End();
private:
	std::shared_ptr<SoundBase> testsound = nullptr;

};