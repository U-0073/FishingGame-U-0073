#pragma once
#include<dsound.h>
#pragma comment(lib, "dsound.lib")
#include<vector>
#include<map>
#include<stdio.h>
#include<string>
#include<d3dx9.h>

using namespace std;

class SoundBase {
private:

	//音源データ構造体
	struct BGMList
	{
		LPDIRECTSOUND3DBUFFER8	LDS3B8;
		LPDIRECTSOUNDBUFFER8	LDSB8;
	};
	struct SEList
	{
		LPDIRECTSOUND3DBUFFER8	LDS3B8;
		LPDIRECTSOUNDBUFFER8	LDSB8;
		D3DXVECTOR3 SEPos;
	};

	//音源データ配列
	map<string, BGMList> BGM_List;
	map<string, SEList> SE_List;

	vector<SEList> List;


public:
	SoundBase();
	~SoundBase();

	void Init(const HWND& hwnd);
	void LoadBGM(const char* fname);
	void LoadSE(const char* fname);

	void CreateSE(const char* Key, const D3DXVECTOR3& PosAdd, int Init, int Loop);

	void Update();

	void PlayBGM(const char* Key, int Init, int Loop);



private:



	//常に単一である情報の定義
	LPDIRECTSOUND3DLISTENER8 lpSListener;



};
