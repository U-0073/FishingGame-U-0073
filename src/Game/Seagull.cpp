#include"../System/KdLibrary/KdLibrary.h"
#include "Seagull.h"

Seagull::Seagull()
{
}

Seagull::~Seagull()
{
}

void Seagull::Init()
{
	//���f���Z�b�g
	m_pModel = RESOURCE_MNG.GetModel("Seagull");
	
	//�����ʒu�����_���z�u
	srand(time(0));
	SeagullPos.x = rand() % 300 - 150;
	SeagullPos.y = rand() % 30 + 80;
	SeagullPos.z = rand() % 300 - 150;

	SeagullPos.y = 0;
	SeagullPos.z = 0;
	SeagullPos.x = 0;
	
}

void Seagull::Update()
{
	
	//�J�����E��]
	SeagullRot.y += 0.1;
	m_world.RotateYLocal(SeagullRot.y);

	//�J�����O���ֈړ�
	SeagullPos.z += 0.2;
	m_world.MoveWorld(SeagullPos);

	//�s��ݒ�
	m_world.SetTrans(SeagullPos);

	//��]�ݒ�
	m_world.SetRotation(SeagullRot.x, SeagullRot.y, SeagullRot.z);


	sound = rand() % 1000;
	if (sound == 0) {
		//�T�E���h
		SeagullVoice = RESOURCE_MNG.GetSound("umineko");
		SeagullVoice->LDS3B8->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		SeagullVoice->LDS3B8->SetPosition(SeagullPos.x, SeagullPos.y, SeagullPos.z, DS3D_IMMEDIATE);
		SeagullVoice->Playsound("umineko", true, false);
	}

}

void Seagull::Draw2D()
{
	SPRITE->End();
	RECT rcText = { 10,0,0,0 };
	char Text[10];
	sprintf_s(Text, sizeof(Text), "SeagullPos x %f y %f z %f", SeagullPos.x, SeagullPos.y, SeagullPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
}

void Seagull::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Seagull::End()
{
	//���f�����
	m_pModel = nullptr;
	//�T�E���h��~
	if (SeagullVoice)	SeagullVoice->LDSB8->Stop();
	//�T�E���h���
	SeagullVoice = nullptr;

}
