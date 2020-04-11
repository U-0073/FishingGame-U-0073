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
	//サウンドデータ構造体
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
	//音源データ配列
	map<std::string, SoundData> Sound_List;

	//常に単一である情報の定義
	LPDIRECTSOUND3DLISTENER8 lpSListener;



};
