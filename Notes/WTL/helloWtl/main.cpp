#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlgdi.h>
#include <atlmisc.h>

static CAppModule appModule;

class CMainWindow
    : public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>
{
    // Карта сообщений направляет сообщения в нужные обработчики.
    BEGIN_MSG_MAP(CMainWindow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    END_MSG_MAP()

    LRESULT OnPaint (UINT /*uMsg*/, WPARAM /*wParam*/,
        LPARAM /*lParam*/, BOOL& bHandled)
    {
        CPaintDC dc (m_hWnd);
        CRect rect;
        GetClientRect (rect);
        dc.DrawText ("\u041F\u0440\u0438\u0432\u0435\u0442, WTL!", -1, rect,
            DT_SINGLELINE|DT_CENTER|DT_VCENTER);

        return 0;
    }

    LRESULT OnDestroy (UINT /*uMsg*/, WPARAM /*wParam*/,
        LPARAM /*lParam*/, BOOL& bHandled)
    {
        PostQuitMessage (0);
        return 0;
    }
};

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    // Инициализируем модуль
    appModule.Init (0, hInstance, 0);

    // Создаём главное окно приложения.
    CMainWindow wnd;
    wnd.Create (nullptr, CWindow::rcDefault,
        "\u041F\u0440\u0438\u0432\u0435\u0442, WTL!");
    wnd.ShowWindow (SW_SHOW);

    // Запускаем цикл сообщений
    CMessageLoop loop;
    auto result = loop.Run();

    // Завершаем программу.
    appModule.Term();

    return result;
}
