#pragma once

class C_Player {
public:
	C_Player();
	~C_Player();

	void Init();		//�������p�֐�
	void Update();
	void Draw3D();

private:
	void Start();		//�Q�[���N�����̏������֐�
	void End();

	KdVec3 PlayerVec;

	int test=0;
};