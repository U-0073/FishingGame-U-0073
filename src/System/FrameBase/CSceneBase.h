#pragma once

class SoundBase;
class CSceneBase
{
public:
	CSceneBase();
	~CSceneBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw2D();
	virtual void Draw3D();

private:


protected:
	enum Scene
	{
		TITLE,
		GAME,
	};


};

