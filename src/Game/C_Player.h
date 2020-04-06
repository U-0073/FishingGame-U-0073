#pragma once

class C_Player {
public:
	C_Player();
	~C_Player();

	void Init();		//‰Šú‰»—pŠÖ”
	void Update();
	void Draw3D();

private:
	void Start();		//ƒQ[ƒ€‹N“®‚Ì‰Šú‰»ŠÖ”
	void End();

	KdVec3 PlayerVec;

	int test=0;
};