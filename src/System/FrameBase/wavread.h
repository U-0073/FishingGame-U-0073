//-----------------------------------------------------------------------------
// File: WavRead.h
//
// Desc: Support for loading and playing Wave files using DirectSound sound
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef WAVE_READ_H
#define WAVE_READ_H


#include <mmsystem.h>
#include <mmreg.h>


//-----------------------------------------------------------------------------
// Name: class CWaveSoundRead
// Desc: A class to read in sound data from a Wave file
//-----------------------------------------------------------------------------
class CWaveSoundRead
{
public:
    WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
    HMMIO         m_hmmioIn;     // MM I/O handle for the WAVE
    MMCKINFO      m_ckIn;        // Multimedia RIFF chunk
    MMCKINFO      m_ckInRiff;    // Use in opening a WAVE file

public:
    CWaveSoundRead();
    ~CWaveSoundRead();

    HRESULT Open( CHAR* strFilename );
    HRESULT Reset();
    HRESULT Read( UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead );
    HRESULT Close();

};


#endif WAVE_READ_H

class SoundBase {
public:
	//�T�E���h�f�[�^�\����
	struct SoundData
	{
		LPDIRECTSOUND3DBUFFER8	LDS3B8;
		LPDIRECTSOUNDBUFFER8	LDSB8;
		D3DXVECTOR3 SEPos;
	};

	SoundBase();
	~SoundBase();

	void Init(const HWND& hwnd);

	void CreateSE(const char* Key, const D3DXVECTOR3& PosAdd, int Init, int Loop);

	void Update();

	void PlayBGM(const char* Key, int Init, int Loop);



private:
	//�����f�[�^�z��
	map<std::string, SoundData> Sound_List;

	//��ɒP��ł�����̒�`
	LPDIRECTSOUND3DLISTENER8 lpSListener;



};
