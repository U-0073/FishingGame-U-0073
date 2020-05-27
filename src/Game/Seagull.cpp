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
	SeagullPos.x = rand() % 150 - 75;
	SeagullPos.y = rand() % 30 + 80;
	SeagullPos.z = rand() % 150 - 75;

	//�s��ݒ�
	//�����ʒu
	m_world.SetTrans(SeagullPos);
}

void Seagull::Update()
{

	//�J�����O���ֈړ�
	m_world.MoveLocal(0,0,0.5);
	//1�t���[���ŉ��x�X��������
	m_world.RotateYLocal(D3DXToRadian(0.75));

	//�J�����̈ʒu���擾
	SeagullPos = m_world.GetPos();

	sound = rand() % 500;
	if (sound == 0) {
		//�T�E���h
		SeagullVoice = RESOURCE_MNG.GetSound("umineko");
		SeagullVoice->LDS3B8->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		SeagullVoice->LDS3B8->SetPosition(SeagullPos.x, 5, SeagullPos.z, DS3D_IMMEDIATE);
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
