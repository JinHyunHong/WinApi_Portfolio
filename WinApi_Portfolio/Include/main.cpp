#include "Game.h"
#include "Logic/Logic.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    if (!GET_SINGLE(CLogic)->Init(hInstance))
    {
        DESTROY_SINGLE(CLogic);
        return 0;
    }

    int iReturnMsg = GET_SINGLE(CLogic)->Run();

    DESTROY_SINGLE(CLogic);

    return iReturnMsg;
}