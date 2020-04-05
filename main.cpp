#include"KdLibrary/KdLibrary.h"

//コメント
//コメントその②

//脇からコメント
//ガッキーさんからの素敵なコメント('_')
//雄也が参加しました。
//ただの鳥が現れた！！( ˘ω˘)ｽﾔｧ 
//林がいじった分
//ビッキーがいじった分
//ワッキーがいじったよおおお
//ンゴ～～～～～～！！！！

//#include<windows.h>
//#include<stdio.h>
//#include<d3dx9.h>
//#include<cassert>
#include"CGameFrame.h"
//
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "winmm.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
    LPSTR lpszCmdParam, int nCmdshow)
{
    MSG msg;

    CGameFrame gameFrame;
    const bool result = gameFrame.Initialize(hInst, nCmdshow);
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
            gameFrame.GameLoop();
        }
    }

    return (int)msg.wParam;
}