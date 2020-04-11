#pragma once


class CSceneBase
{
public:
	CSceneBase();
	~CSceneBase();

	virtual void Update();
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	std::shared_ptr<SoundBase> m_PSound;
	


};

