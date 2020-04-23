#pragma once



class CSceneBase;
class CMapScene;
class CTitleScene;
class CShopScene;

class CCamera;


class CGameFrame
{
public:



	const bool Initialize(HINSTANCE aHInst, const int aCmdShow);
	void GameLoop();
	const HWND& GetHWND() { return mpHwnd; }

private:
	CGameFrame();
	~CGameFrame();
	const bool CreateWNDCLASS(HINSTANCE aHInst);
	const bool CreateHWND(HINSTANCE aHInst, const int aCmdShow);
	const bool CreateDirectX9();

	HWND					mpHwnd;
	
	   
	WNDCLASS				mWndClass;


	std::shared_ptr<CSceneBase> nowScene = nullptr;
	
	bool              mIsFullScreen;
	const D3DXVECTOR2       mWindowSize;
	const std::string       mAppName;

	int nextscene;


public:
	static CGameFrame& GetInstance()
	{
		static CGameFrame instance;
		return instance;

	}
};
#define FRAME CGameFrame::GetInstance()
#define GETHWND FRAME.GetHWND()
