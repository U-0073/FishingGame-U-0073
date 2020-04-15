#pragma once
#include"../System/FrameBase/CSceneBase.h"


class CTitleScene : public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

	void Init()override;
	void Update()override;
	void Draw2D()override;
	void Draw3D()override;

private:
};