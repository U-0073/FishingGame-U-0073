#pragma once

class CFade
{
private:
	CFade();
	~CFade();
public:
	void Update();
	void Draw();
	void Start(const float& speed) {
		startflg = true;
		accel = speed * 60 / 255;
	};

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
#define FADE CFade::GetInstance()