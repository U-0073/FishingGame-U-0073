#include"../KdLibrary/KdLibrary.h"


#include"CGameFrame.h"



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
    LPSTR lpszCmdParam, int nCmdshow)
{
    MSG msg;
 
    const bool result = FRAME.Initialize(hInst, nCmdshow);


    /*  CGameFrame gameFrame;*/
    

    if( result == false )
    {
        _ASSERT_EXPR( 0 , L"CGameFrame Initialize Error " );
        return 0;
    }


   // メモリリークを知らせる
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // COM初期化
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    
    
    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            FRAME.GameLoop();
        }
    }
    // COM解放
    CoUninitialize();
    return (int)msg.wParam;
}