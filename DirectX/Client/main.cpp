#include "Engine.h"
#include "resource.h"

#ifdef _DEBUG
// 라이브러리 링크를 걸어준다.
#pragma comment(lib, "GameEngine_Debug.lib")

#else

#pragma comment(lib, "GameEngine.lib")

#endif // _DEBUG


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    if (!CEngine::GetInst()->Init(hInstance,TEXT("Windows"),
        IDI_ICON1,IDI_ICON1,1280,720))
    {
        CEngine::DestroyInst();
    }

    return 0;
}