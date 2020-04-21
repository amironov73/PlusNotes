### Простейшее оконное приложение Win32

Напоминаю себе о том, как создать простейшее окно с помощью Win32 API.

```c++
#include <windows.h>
#include <string>
 
static const char CLASS_NAME[] = "Sample Window Class";
static HWND mainWindow;
std::string mainText ("Hello, world!");;
 
static LRESULT CALLBACK MyWindowProc (HWND hwnd, UINT uMsg, 
    WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
 
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint (hwnd, &ps);
 
            FillRect (hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            DrawText (hdc, mainText.data(), mainText.size(), &ps.rcPaint,
                    DT_NOPREFIX|DT_CENTER|DT_VCENTER);
 
            EndPaint (hwnd, &ps);
        }
            return 0;
    }
 
    return DefWindowProc (hwnd, uMsg, wParam, lParam);
}
 
static void registerClass (HINSTANCE hInstance)
{
    WNDCLASS wc {};
    wc.lpfnWndProc   = MyWindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
 
    RegisterClass (&wc);
}
 
static void createWindow (HINSTANCE hInstance)
{
    DWORD style = WS_CAPTION|WS_SYSMENU;
    DWORD styleEx = WS_EX_TOOLWINDOW;
 
    mainWindow = CreateWindowEx
        (
            styleEx,              // Optional window styles
            CLASS_NAME,           // Window class
            "Learn WinAPI",       // Window text
            style,                // Window style
 
            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, 250, 70,
 
            nullptr,       // Parent window
            nullptr,       // Menu
            hInstance,     // Instance handle
            nullptr        // Additional application data
        );
 
}
 
static void messageLoop()
{
    MSG msg {};
    while (GetMessage (&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
 
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE, 
    PSTR pCmdLine, int nCmdShow)
{
    registerClass (hInstance);
    createWindow (hInstance);
    ShowWindow (mainWindow, nCmdShow);
    messageLoop();
 
    return 0;
}
```
