﻿#pragma once

class SoundBase;
class CSceneBase
{
public:
	CSceneBase();
	~CSceneBase();

	virtual void Init();
	virtual int Update();
	virtual void Draw2D();
	virtual void Draw3D();

private:


protected:



};

