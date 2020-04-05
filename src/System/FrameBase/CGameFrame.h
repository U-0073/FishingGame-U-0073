#pragma once



class CGameScene;

class CGameFrame
{
public:

	CGameFrame();
	~CGameFrame();

    const bool Initialize(HINSTANCE aHInst, const int aCmdShow);
    void GameLoop();

private:

    const bool CreateWNDCLASS(HINSTANCE aHInst);
    const bool CreateHWND(HINSTANCE aHInst, const int aCmdShow);
    const bool CreateDirectX9();

    HWND					mpHwnd;
 /*  
    LPDIRECT3D9				mpD3D;
    LPDIRECT3DDEVICE9		mpD3DDevice;
    D3DPRESENT_PARAMETERS	mD3Dpp;
    */
    WNDCLASS				mWndClass;
    

    CGameScene *            mpScene;
    const bool              mIsFullScreen;
    const D3DXVECTOR2       mWindowSize;
    const std::string       mAppName;

};

