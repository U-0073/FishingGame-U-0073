#pragma once

class C_Player {
public:
	C_Player();
	~C_Player();

	void Init();		//初期化用関数
	void Update();
	void Draw3D();

private:
	void Start();		//ゲーム起動時の初期化関数
	void End();

	KdVec3 PlayerVec;

	int test=0;
};