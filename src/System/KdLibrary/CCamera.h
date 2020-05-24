#pragma once


class CCamera {
private:
	CCamera();
	~CCamera();


public:
	void Set(const D3DXVECTOR2& mWindowSize);
	void SetCameraPos(const KdVec3& Pos, const KdVec3& LookPos);
	void SetCameraVec(const KdVec3& Pos, const KdVec3& LookVec);
	KdVec3& GetCameraPos() { return Pos; }
	KdVec3& GetCameraVec() {
		return LookVec;
	}

public:
	static CCamera& GetInstance()
	{
		static CCamera instance;
		return instance;

	}

	LPDIRECTSOUND3DLISTENER8 lpSListener;

private:

	KdVec3	Pos;

	KdVec3	LookVec;

	KdVec3	HeadPos;
};
#define CAMERA CCamera::GetInstance()

