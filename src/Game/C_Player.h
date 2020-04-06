#pragma once

#include"../System/FrameBase/GameObject.h"

class C_Player :public GameObject{
public:
	C_Player();
	~C_Player();

	void Init()override;		//�������p�֐�
	void Update()override;
	void Draw3D()override;
	void Draw2D()override;

private:
	void Start();		//�Q�[���N�����̏������֐�
	void End();

	KdVec3			PlayerVec;
	KdVec3			StartVec;		//�����ʒu

	int test=0;
};