#include "GameMain.h"
#include "DxLib.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // ������printf���g����
    printf("Hello, Console!\n");

    // �Q�[���̋N��
    GameMain gameMain;
    gameMain.Run();

    return 0;
}