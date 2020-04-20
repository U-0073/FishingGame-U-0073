#include"../KdLibrary/KdLibrary.h"
#include"Fade.h"

void CFade::Init()
{
	vTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/white.png", 3, 3, NULL);
	KdMatrix vScale;
	vScale.CreateScale(1280, 720, 0);
	vMat.CreateTrans(1280 / 2, 720 / 2, 0);
	vMat = vScale * vMat;
}

void CFade::Update(float& speed)
{
	accel = 255 / speed * 60;
	if (startflg) {
		//�����Z���Ȃ�
		alpha += accel;
		if (alpha > 255) {
			alpha = 255;
			accel *= -1;
		}
		//���������Ȃ�
		alpha += accel;
		if (alpha < 0) {
			alpha = 0;
			startflg = 0;
		}

	}
}

void CFade::Draw()
{
	RECT rc = { 1,1,2,2 };
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	SPRITE->SetTransform(&vMat);
	SPRITE->Draw(vTex, &rc, &D3DXVECTOR3(0.5f, 0.5f, 0.0f), NULL, D3DCOLOR_ARGB((int)alpha, 255, 255, 255));
	SPRITE->End();
}
