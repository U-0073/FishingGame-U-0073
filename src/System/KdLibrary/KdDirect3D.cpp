#include "KdLibrary.h"

#include "KdDirect3D.h"


//================================================================================
//
// Direct3D9Exを初期化する。
//	引数：hWnd･･･Direct3Dで使用するウィンドウ
//	　　　Width･･･幅
//　　　　Height･･･高さ
//　　　　Format･･･色モード
//　　　　FullScreen･･･フルスクリーンフラグ
//　戻り値：成功･･･TRUE
//　　　　　失敗･･･FALSE
//
//================================================================================
bool KdDirect3D::Init(HWND hWnd, int width, int height, bool fullscreen, std::string& errorMsg)
{
	HRESULT hr;

	//=======================================================
	// D3Dオブジェクト作成
	//=======================================================
	hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_lpD3D);
	if(FAILED(hr)){
		return false;
	}

	//=======================================================
	// 現在の画面モードを取得
	//=======================================================
	D3DDISPLAYMODE d3ddm;
	hr = m_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(hr)) {
		Release();
		return false;
	}

	//=======================================================
	// デバイス作成のための設定
	//=======================================================
	ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	m_d3dpp.BackBufferCount = 2;
	// フルスクリーンモード時
	if (fullscreen){
		m_d3dpp.Windowed = FALSE;
		m_d3dpp.BackBufferWidth = width;
		m_d3dpp.BackBufferHeight = height;
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dpp.FullScreen_RefreshRateInHz = 60;
	}
	// ウィンドウモード時
	else{
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.BackBufferWidth = 0;
		m_d3dpp.BackBufferHeight = 0;
		m_d3dpp.BackBufferFormat = d3ddm.Format;
	}
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	// スワップエフェクト
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// モニタの垂直同期を待たない
	m_d3dpp.hDeviceWindow = hWnd;
	// Z バッファの自動作成
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 24bitZバッファ + 8bitステンシルバッファ

	// ディスプレイモード設定(FullScreen時のみ使用)
	D3DDISPLAYMODEEX dm;
	dm.Width = width;
	dm.Height = height;
	dm.Format = m_d3dpp.BackBufferFormat;
	dm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
	dm.RefreshRate = m_d3dpp.FullScreen_RefreshRateInHz;
	dm.Size = sizeof(dm);

	//=======================================================
	// デバイスの作成
	//=======================================================
	// ※D3DCREATE_MULTITHREADED	…　マルチスレッドでのデバイス操作を許可
	// ※D3DCREATE_FPU_PRESERVE		…　floatの制度を下げずに維持する(高精度なfloatを使う)
	DWORD flags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE;

	hr = m_lpD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, flags, &m_d3dpp, (fullscreen ? &dm : nullptr), &m_lpD3DDev);
	if(FAILED(hr))
	{
		// 失敗
		errorMsg = "Direct3Dの初期化に失敗", "Direct3D初期化";

		// 終了する
		Release();
		return false;
	}

	//=======================================================
	// Caps取得
	//=======================================================
	m_lpD3DDev->GetDeviceCaps(&m_Caps);
	
	//=======================================================
	// デフォルトのバックバッファとZバッファ取得しておく
	//=======================================================
	m_lpD3DDev->GetRenderTarget(0, &m_OrgRenderTarget);
	m_lpD3DDev->GetDepthStencilSurface(&m_OrgDepthStencil);


	//=======================================================
	// デフォルトのビュー行列とプロジェクション行列を設定
	//=======================================================
	// まずカメラの行列を作る
	D3DXMATRIX mView;
	D3DXMatrixTranslation(&mView, 0, 0, -10.0f);	// 
	// 逆行列でビュー行列へ変換しセット
	D3DXMatrixInverse(&mView, 0, &mView);
	m_lpD3DDev->SetTransform(D3DTS_VIEW, &mView);

	// 射影行列
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)width/height, 0.1f, 2000.0f);
	m_lpD3DDev->SetTransform(D3DTS_PROJECTION, &mProj);

	//ライト設定
	m_Light.Type = D3DLIGHT_DIRECTIONAL;//平行光線
	//ライトの色
	m_Light.Diffuse.a = 1.0f;
	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;

	//光届かぬ地に光明を
	m_Light.Ambient.a = 1.0f;
	m_Light.Ambient.r = 0.2f;
	m_Light.Ambient.g = 0.2f;
	m_Light.Ambient.b = 0.2f;

	//光差す方へ
	auto dir = KdVec3(0.5f, -1, 1);
	dir.Normalize();
	m_Light.Direction = dir;

	//ライトのセット
	m_lpD3DDev->SetLight(0, &m_Light);

	//ライトを有効にする
	m_lpD3DDev->LightEnable(0, true);


	// スプライト作成.
	D3DXCreateSprite(m_lpD3DDev, &mpSprite);
	mpSprite->OnResetDevice();

	// フォント作成
	D3DXCreateFont(m_lpD3DDev, 20, 20, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &mpFont);
	mpFont->OnResetDevice();
	return true;
}

void KdDirect3D::Release()
{
	// バックバッファとZバッファ解放
	KdSafeRelease(m_OrgRenderTarget);
	KdSafeRelease(m_OrgDepthStencil);

	// デバイス解放
	KdSafeRelease(m_lpD3DDev);
	// Direct3D解放
	KdSafeRelease(m_lpD3D);
}

bool KdDirect3D::ChangeFullScreenMode()
{

	// フルスクリーンモードへ
	if (m_d3dpp.Windowed) {
		m_d3dpp.Windowed = FALSE;
		m_d3dpp.FullScreen_RefreshRateInHz = 60;
	}
	// ウィンドウモードへ
	else {
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.BackBufferWidth = 0;
		m_d3dpp.BackBufferHeight = 0;
		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	}

	// ディスプレイモード設定(FullScreen時のみ)
	D3DDISPLAYMODEEX dm;
	dm.Width = m_d3dpp.BackBufferWidth;
	dm.Height = m_d3dpp.BackBufferHeight;
	dm.Format = m_d3dpp.BackBufferFormat;
	dm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
	dm.RefreshRate = m_d3dpp.FullScreen_RefreshRateInHz;
	dm.Size = sizeof(dm);

	// 
	HRESULT hr = m_lpD3DDev->ResetEx(&m_d3dpp, m_d3dpp.Windowed ? nullptr : &dm);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//================================================================================
//
// 基本的かなぁと思うレンダーステートの設定
//
//================================================================================
void KdDirect3D::SetDefaultState()
{
	// DirectGraphicsの詳細設定
	m_lpD3DDev->SetRenderState(D3DRS_ZENABLE,TRUE);					// Zバッファ有効
	m_lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);			// Zバッファに書き込み有効
	m_lpD3DDev->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
	m_lpD3DDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		// アルファブレンド有効

	// 半透明モード
	m_lpD3DDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_lpD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_lpD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_lpD3DDev->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);		//頂点法線の自動正規化

	m_lpD3DDev->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	// グローシェーディング
	m_lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);		// カリング CCW = 右回り = 表面のみ描画

	// アルファ値個別計算
	m_lpD3DDev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	m_lpD3DDev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
	m_lpD3DDev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	m_lpD3DDev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);

	// テクスチャのα値のブレンディング方法の設定
	// テクスチャα合成処理の方法
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );    // 以下の引数の成分を乗算する
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );    // テクスチャの色を使用
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );    // 頂点の色を使用
	// 色を合成する方法
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );    // 以下の引数の成分を乗算する
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );    // テクスチャの色を使用
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );    // 頂点の色を使用

	// テクスチャ補間を線形に
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// テクスチャアドレッシングモード設定
	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);	// ラップモード
	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);	// ラップモード

	// ミップマップ詳細レベルを設定する。
	float fMipBias = 0.0f;
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fMipBias));

	// ライトOFF
	m_lpD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// スペキュラ有効
	m_lpD3DDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// フォグ(霧効果)
	m_lpD3DDev->SetRenderState(D3DRS_FOGENABLE, FALSE);
}
