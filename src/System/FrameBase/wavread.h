#pragma once

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

	HRESULT Open(CHAR* strFilename);
	HRESULT Reset();
	HRESULT Read(UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead);
	HRESULT Close();

};
#endif WAVE_READ_H


class SoundBase {
public:
	SoundBase();
	~SoundBase();
	
	void SetPos(D3DXVECTOR3& Pos);

	bool Loadsound(const std::string& fname);

	void Copysound(const std::string& Key, int Init, int Loop);

	void Update();

	void Playsound(const std::string& Key, bool Init, bool Loop);


	//0.0～1.0
	void SetVol(float Volume) {
		if (Volume < 0)Volume = 0;
		LDSB8->SetVolume(-5000 + (5000 * Volume)); }
	void SetFreq(const float& Freq) { LDSB8->SetFrequency(Hz * Freq); }

	LPDIRECTSOUND3DBUFFER8	LDS3B8;
	LPDIRECTSOUNDBUFFER8	LDSB8;
	D3DXVECTOR3 SoundPos;
private:

	//音量
	int volume;
	//周波数
	DWORD Hz;
	//プライマリバッファの音量
	long masterVol;


};