﻿#include"../KdLibrary/KdLibrary.h"

//#include<windows.h>
//#include<stdio.h>
//#include<d3dx9.h>
//#include<cassert>

#include"CGameFrame.h"

//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "winmm.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
    LPSTR lpszCmdParam, int nCmdshow)
{
    MSG msg;
    // メモリリークを知らせる
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  
    /*  CGameFrame gameFrame;*/
    
    const bool result = FRAME.Initialize(hInst, nCmdshow);
    if( result == false )
    {
        _ASSERT_EXPR( 0 , L"CGameFrame Initialize Error " );
        return 0;
    }

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

    return (int)msg.wParam;
}