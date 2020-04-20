#pragma once

class CFade
{
public:
	void Init();
	void Update(float &speed);
	void Draw();
	void Start() { startflg = true; };

private:
	bool startflg;
	LPDIRECT3DTEXTURE9 vTex;
	KdMatrix vMat;
	float alpha;
	float accel;
public:
	static CFade& GetInstance()
	{
		static CFade instance;
		return instance;
	}
};
#define FADE CFade::GetInstance();