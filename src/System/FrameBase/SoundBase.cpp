#include "../FrameBase/SoundBase.h"
#include "../FrameBase/wavread.h"



SoundBase::SoundBase()
{
	//==================================================
	//パスの生成
	//==================================================
}

SoundBase::~SoundBase()
{
	BGM_List.clear();
	SE_List.clear();
	List.clear();

}

void SoundBase::Init(const HWND &hwnd)
{
}

void SoundBase::LoadBGM(const char *fname)//（音の読込）
{

}

void SoundBase::CreateSE(const char * Key, const D3DXVECTOR3 &PosAdd, int Init, int Loop)
{
	SEList tmp;
	//コピー
	LPDIRECTSOUNDBUFFER lpSTmp;
	KD3D.GetlpDSound()->DuplicateSoundBuffer(SE_List[Key].LDSB8, &lpSTmp);
	lpSTmp	 ->QueryInterface(IID_IDirectSoundBuffer8,   (LPVOID *)&tmp.LDSB8);
	tmp.LDSB8->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&tmp.LDS3B8);
	tmp.LDS3B8->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);

	List.emplace_back(tmp);

	List[(List.size() - 1)].SEPos = PosAdd;
	tmp.LDS3B8->SetPosition(List[(List.size() - 1)].SEPos.x, List[(List.size() - 1)].SEPos.y, List[(List.size() - 1)].SEPos.z, DS3D_IMMEDIATE);
	lpSTmp->Release();


	if (Init)	List[(List.size() - 1)].LDSB8->SetCurrentPosition(0);
	if (Loop)	List[(List.size() - 1)].LDSB8->Play(0, 0, DSBPLAY_LOOPING);
	else		List[(List.size() - 1)].LDSB8->Play(0, 0, 0);

}

void SoundBase::Update()
{
	//lpSListener->SetPosition();


	for (int i = 0; i < List.size(); i++)
	{		
		DWORD sFlg;
		List[i].LDSB8->GetStatus(&sFlg);
		if (!(sFlg & DSBSTATUS_PLAYING)) {
			List.erase(List.begin() + i);
				break;
		}
	}
}


void SoundBase::PlayBGM(const char * Key, int Init, int Loop)
{
		if (Init)
		{
			BGM_List[Key].LDSB8->SetCurrentPosition(0);
		}
		if (!Loop)
		{
			BGM_List[Key].LDSB8->Play(0, 0, 0);
		}
		else
		{
			BGM_List[Key].LDSB8->Play(0, 0, DSBPLAY_LOOPING);
		}
}
