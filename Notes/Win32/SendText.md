### Как «напечатать» строку в чужом окне

```c++
#include <windows.h>
#include <cstring>
#include <iostream>
 
static void sendText (HWND hwnd, const std::wstring &text)
{
    for (const auto c : text) {
        SendMessageW (hwnd, WM_CHAR, c, 0);
        Sleep (10);
    }
}
 
int main()
{
    // Отыскиваем окно, находящееся на переднем плане
    HWND hwnd = GetForegroundWindow();
    std::cout << "ForegroundWindow: " << std::ios::hex << hwnd << std::endl;
 
    // Выводим заголовок этого окна (чисто для самоконтроля)
    char title[256];
    memset (title, 0, sizeof (title));
    GetWindowTextA(hwnd, title, sizeof (title));
    std::cout << "Title: " << title << std::endl;
 
    // Получаем идентификатор потока, создавшего это окно
    DWORD threadId = GetWindowThreadProcessId (hwnd, nullptr);
    std::cout << "Thread ID: " << std::ios::hex << threadId << std::endl;
 
    // Получаем разнообразную информацию об этом окне
    GUITHREADINFO gui;
    memset (&gui, 0, sizeof (gui));
    gui.cbSize = sizeof (gui);
    GetGUIThreadInfo (threadId, &gui);
 
    // Кроме прочего, окно, в котором находится каретка 
    // (окно, принимающее клавиатурный ввод)
    HWND hcaret = gui.hwndCaret;
    std::cout << "HWND caret: " << std::ios::hex << hcaret << std::endl;
 
    // Побуквенно отсылаем туда текст "Привет, мир!"
    sendText (hcaret, L"\u041F\u0440\u0438\u0432\u0435\u0442, "
       L"\u043C\u0438\u0440!");
}
```
