#include"../KdLibrary/KdLibrary.h"
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
		ShowCursor(FALSE);
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
	DTWHOUCE.SetStr("FishName", "Sunfish");//何の魚もつれていない//デバック
	DTWHOUCE.SetInt("Possession", 999999999);
	nowscene = nowScene->GetID();
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
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case TITLE:
				nowScene = std::make_shared<CTitleScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case GAME:
				nowScene = std::make_shared<CGameScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case MAP:
				nowScene = std::make_shared<CMapScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case SHOP:
				nowScene = std::make_shared<CShopScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			case RESULT:
				nowScene = std::make_shared<CResultScene>();
				nowScene->Init();
				nowscene = nowScene->GetID();//シーンIDの保存
				break;
			}


			//nowScene->Update();
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

	//CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -0.5), D3DXVECTOR3(0, 0, 1));

	CAMERA.Set(mWindowSize);

	if (nowScene) {


		//2D描画.
		SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
		nowScene->Draw2D();
		SPRITE->End();

		//3D描画.
		KD3D.SetLights();
		nowScene->Draw3D();

	}
	FADE.Draw();
	RECT rc = { 0,0,0,0 };
	char buf[100];
	sprintf_s(buf, sizeof(buf), "%dFPS", FPS);
	FONT->DrawText(NULL, buf, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));


	// 描画終了
	KD3D.GetDev()->EndScene();

	// バックバッファをプライマリバッファにコピー
	KD3D.GetDev()->Present(NULL, NULL, NULL, NULL);
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
//
//const bool CGameFrame::CreateDirectX9()
//{
//
//
//	{
//	// Direct3D オブジェクトを作成
//	mpD3D = Direct3DCreate9(D3D_SDK_VERSION);
//	if (mpD3D == nullptr)
//	{
//		// オブジェクト作成失敗
//		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
//		// 終了する
//		return false;
//	}
//	int adapter;
//
//	// 使用するアダプタ番号
//	adapter = D3DADAPTER_DEFAULT;
//
//	// ウインドウの作成が完了したので、Direct3D を初期化する
//	ZeroMemory(&mD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
//	// Direct3D 初期化パラメータの設定
//	if (mIsFullScreen)
//	{
//		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
//		mD3Dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
//	}
//	else
//	{
//		// ウインドウ : 現在の画面モードを使用
//		D3DDISPLAYMODE disp;
//		// 現在の画面モードを取得
//		mpD3D->GetAdapterDisplayMode(adapter, &disp);
//		mD3Dpp.BackBufferFormat = disp.Format;
//	}
//	// 表示領域サイズの設定
//	mD3Dpp.BackBufferWidth = static_cast<UINT>(mWindowSize.x);
//	mD3Dpp.BackBufferHeight = static_cast<UINT>(mWindowSize.y);
//	mD3Dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
//
//	if (mIsFullScreen == false)
//	{
//		// ウインドウモード
//		mD3Dpp.Windowed = 1;
//	}
//
//	// Z バッファの自動作成
//	mD3Dpp.EnableAutoDepthStencil = 1;
//	mD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
//
//	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
//	mD3Dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
//
//	// デバイスの作成 - T&L HAL
//	if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, mpHwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
//	{
//		// 失敗したので HAL で試行
//		if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, mpHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
//		{
//			// 失敗したので REF で試行
//			if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, mpHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
//			{
//				// 結局失敗した
//				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);
//				mpD3D->Release();
//				// 終了する
//				return false;
//			}
//		}
//	}
//
//	// レンダリング・ステートを設定
//	// Z バッファ有効化->前後関係の計算を正確にしてくれる
//	mpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//	mpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//
//	// アルファブレンディング有効化
//	mpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//
//	// アルファブレンディング方法を設定
//	mpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	mpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	// レンダリング時のアルファ値の計算方法の設定
//	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
//	// テクスチャの色を使用
//	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	// 頂点の色を使用
//	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
//	// レンダリング時の色の計算方法の設定
//	mpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
//
//	//裏面カリング
//	mpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//	// フィルタ設定
//	mpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
//	mpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
//	mpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//
//	// ライト
//	mpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	mpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
//	// 頂点フォーマットの設定
//	mpD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//	return true;
//
//}
//
//
//}
