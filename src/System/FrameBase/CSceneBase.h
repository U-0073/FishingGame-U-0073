#pragma once

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
	virtual int GetID() = 0;
	virtual void End() {};
	virtual std::string GetData() { return ""; };
	virtual void SetData(std::string) {};

private:


protected:



};

