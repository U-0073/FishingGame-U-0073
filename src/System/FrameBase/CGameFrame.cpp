﻿#include"../KdLibrary/KdLibrary.h"
#include "CGameFrame.h"
#include "CSceneBase.h"
#include"../../Game/Scene/CRogoScene.h"
#include"../../Game/Scene/CTitleScene.h"
#include"../../Game/Scene/CMapScene.h"
#include"../../Game/Scene/CGameScene.h"
#include"../../Game/Scene/CResultScene.h"
#include"../../Game/Scene/CShopScene.h"

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CLOSE:
		if (MessageBox(hwnd, "終了しますか？", "終了メニュー", MB_ICONQUESTION | MB_YESNO) == IDYES) {
			PostQuitMessage(0);
		}
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			if (MessageBox(hwnd, "終了しますか？", "終了メニュー", MB_ICONQUESTION | MB_YESNO) == IDYES) {
				PostQuitMessage(0);
			}
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

//コンストラクタ(インスタンス化(作られたとき)時に呼び出される関数)
CGameFrame::CGameFrame()
	: mpHwnd(nullptr)
	//, mpD3D( nullptr )
	//, mpD3DDevice( nullptr )
	//, mD3Dpp()
	, mWndClass()
	, nowScene(nullptr)
	, mIsFullScreen(false)
	, mWindowSize(1280, 720)
	, mAppName("ANGLERS")

{


}

//デストラクタ(破棄した時(メモリから解放)に呼び出される関数)
CGameFrame::~CGameFrame()
{
	nowScene = nullptr;
}

const bool CGameFrame::CreateHWND(HINSTANCE aHInst, const int aCmdShow)
{
	mpHwnd = CreateWindowEx(
		0,
		mAppName.c_str(),
		mAppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<int>(mWindowSize.x), static_cast<int>(mWindowSize.y),
		NULL, NULL, aHInst,
		NULL);

	if (!mpHwnd)return false;

	ShowWindow(mpHwnd, aCmdShow);
	UpdateWindow(mpHwnd);
	SetFocus(mpHwnd);

	mIsFullScreen = false;	// ウィンドウモード
	if (MessageBox(mpHwnd, "フルスクリーンにしますか？", "フルスクリーン?", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES) {
		mIsFullScreen = true;
	}


	if (mIsFullScreen) {
		
	}
	else {
		RECT rc = { 0,0, static_cast<LONG>(mWindowSize.x), static_cast<LONG>(mWindowSize.y) };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(mpHwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}


	return true;
}
//初期化関数、ウィンドウとDirectX関連に必要なものを生成する.
const bool CGameFrame::Initialize(HINSTANCE aHInst, const int aCmdShow)
{
	if (CreateWNDCLASS(aHInst) == false) { return false; }

	if (CreateHWND(aHInst, aCmdShow) == false) { return false; }

	if (CreateDirectX9() == false) { return false; }


	nowScene = std::make_shared<CRogoScene>();
	nowScene->Init();
	DTWHOUCE.SetStr("FishName", "Shark");//何の魚もつれていない//デバック
	DTWHOUCE.SetInt("Possession", 2000);
	nowscene = nowScene->GetID();
	MShowSwich(false);
	CAMERA.Set(mWindowSize);

	return true;
}

void CGameFrame::GameLoop()
{
	NT = timeGetTime();
	if (NT - PT < 1000 / 60) {
		return;
	}
	else {
		PT = NT;
	}
	NowTime = timeGetTime();
	if (NowTime - PrevTime >= 1000) {
		PrevTime = NowTime;
		FPS = cnt;
		cnt = 0;
	}
	cnt++;
	DWORD flags =
		D3DCLEAR_TARGET | // ARGB情報
		D3DCLEAR_ZBUFFER | // 奥行情報
		D3DCLEAR_STENCIL;	// マスク用情報



	if (nextscene != nowscene)//シーンIDの比較
	{


		if (FADE.GetLoadOKFlg()) {

			SceneClear();
			switch (nextscene)
			{
			case ROGO:
				nowScene = std::make_shared<CRogoScene>();
				nowScene->Init();
				MShowSwich(true);
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case TITLE:
				nowScene = std::make_shared<CTitleScene>();
				nowScene->Init();
				MShowSwich(false);
				nowscene = nowScene->GetID();//シーンIDの保存

				break;
			case GAME:
				nowScene = std::make_shared<CGameScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				MShowSwich(true);
				//ShowCursor(TRUE);
				break;
			case MAP:
				nowScene = std::make_shared<CMapScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				MShowSwich(false);
				break;
			case SHOP:
				nowScene = std::make_shared<CShopScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				MShowSwich(false);
				break;
			case RESULT:
				nowScene = std::make_shared<CResultScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				MShowSwich(false);
				break;
			}


		}
	}

	KD3D.GetDev()->Clear(0, nullptr, flags, D3DCOLOR_ARGB(255, 0, 0, 255), 1.0f, 0);


	//nowSceneが存在してnextsceneとnowsceneが同じかどうか
	if (nowScene && nextscene == nowscene) {
		//シーンの更新
		nextscene = nowScene->Update();

	}
	else if(nextscene != nowscene) {
		nowScene->Update();
	}




	FADE.Update();

	// 描画開始
	KD3D.GetDev()->BeginScene();

	CAMERA.Set(mWindowSize);

	if (nowScene) {

		//3D描画.
		KD3D.SetLights();
		nowScene->Draw3D();

		//2D描画.
		SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
		nowScene->Draw2D();
		SPRITE->End();


	}
	FADE.Draw();

	// 描画終了
	KD3D.GetDev()->EndScene();

	// バックバッファをプライマリバッファにコピー
	KD3D.GetDev()->Present(NULL, NULL, NULL, NULL);
}

void CGameFrame::MShowSwich(bool on_off)
{


	if (mSS == on_off)return;
	else {
		mSS = on_off;
		if(mSS==true)ShowCursor(TRUE);
		else ShowCursor(FALSE);
	}

}

const bool CGameFrame::CreateWNDCLASS(HINSTANCE aHInst)
{
	WNDCLASS result;
	result.style = CS_DBLCLKS;
	result.lpfnWndProc = WndFunc;
	result.cbClsExtra = 0;
	result.cbWndExtra = 0;
	result.hInstance = aHInst;
	result.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	result.hCursor = LoadCursor(NULL, IDC_ARROW);
	result.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	result.lpszMenuName = NULL;
	result.lpszClassName = mAppName.c_str();

	RegisterClass(&result);
	return true;
}


const bool CGameFrame::CreateDirectX9() {
	//	//===================================================================
	//	// Direct3D初期化
	//	//===================================================================
	std::string errorMsg;
	if (KD3D.Init(mpHwnd, mWindowSize.x, mWindowSize.y, mIsFullScreen, errorMsg) == false) {
		MessageBox(mpHwnd, errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}
	KD3D.SetDefaultState();
	return true;
}
void CGameFrame::SceneClear()
{
	if (nowScene) {
		nowScene->End();
		nowScene = nullptr;
		KD3D.DeleteLight();
	}
}
