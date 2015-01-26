#pragma warning( disable : 4996)
#define LOG_ON		1
#define FFT_SIZE	32768//32768//1024
//build 020_001_58

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <commctrl.h>
#include "bass.h"
#include "bass_info.cpp"
#include "..//..//libraries//mylibs//error_handler//error_handler.cpp"
#include "..//..//libraries//mylibs//mylibs_10.cpp"
#include "..//..//libraries//mylibs//my_wave_lib-6.cpp"
#include "..//..//libraries//mylibs//dirz.cpp"

#include "..//..//libraries//FFT_CODE\complex.cpp"
#include "..//..//libraries//FFT_CODE\fft.cpp"
#include "Fourier.cpp"

#include "Fourier_.cpp"
#include "fft.h"

#include "globals.cpp"

#include "bass_functions.cpp"

#include "functions.cpp"
#include "proc_main.cpp" 

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib,"..\\..\\libraries\\bass24\\bass.lib")

const wchar_t szClassName[] = L"FFT Signal";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 

//plusSignals(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\3.wav", L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\2.wav", L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\4.wav", 2);
InitCommonControls();

    WNDCLASSEXW wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = proc_main;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 20, 0));
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassExW(&wc))
    {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	hwnd = CreateWindowExW(0, szClassName, L"FFT Signal", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 800, NULL, NULL, hInstance, NULL);

	hwnd_main = hwnd;

    if(hwnd == NULL)
    {
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessageW(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessageW(&Msg);
    }
    return Msg.wParam;
}
