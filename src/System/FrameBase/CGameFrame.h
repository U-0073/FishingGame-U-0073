#pragma once



class CSceneBase;
class CRogoScene;
class CTitleScene;
class CMapScene;
class CGameScene;
class CResultScene;
class CShopScene;

class CCamera;

class CGameFrame
{
public:

	const bool Initialize(HINSTANCE aHInst, const int aCmdShow);
	void GameLoop();
	const HWND& GetHWND() { return mpHwnd; }

	//
	//マウスカーソルのオンオフ設定用関数
//現状がtrueならfalse以外は処理をしない
//現状がfalseならtrue以外は処理をしない

	
private:
	void MShowSwich(bool on_off);

	//マウス見えるか保存
	bool mSS=true;


	CGameFrame();
	~CGameFrame();
	const bool CreateWNDCLASS(HINSTANCE aHInst);
	const bool CreateHWND(HINSTANCE aHInst, const int aCmdShow);
	const bool CreateDirectX9();
	void SceneClear();

	HWND					mpHwnd;
	
	   
	WNDCLASS				mWndClass;


	std::shared_ptr<CSceneBase> nowScene = nullptr;
	
	bool              mIsFullScreen;
	const D3DXVECTOR2       mWindowSize;
	const std::string       mAppName;

	int nextscene,nowscene;

	DWORD NowTime, NT;
	DWORD PrevTime, PT;
	int cnt;
	int FPS;


public:
	static CGameFrame& GetInstance()
	{
		static CGameFrame instance;
		return instance;

	}
};
#define FRAME CGameFrame::GetInstance()
#define GETHWND FRAME.GetHWND()
