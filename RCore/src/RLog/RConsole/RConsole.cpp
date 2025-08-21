#include "RConsole.h"
#include <windows.h>
#include <commctrl.h>

#define WM_CONSOLE_LOG (WM_USER + 1)
#define ACTION_CLEAR 1
#define ACTION_COPY 2

class RConsole;

LRESULT CALLBACK AppLogWindowWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    RConsole* pLogConsole = reinterpret_cast<RConsole*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    if (pLogConsole == nullptr) return DefWindowProcW(hwnd, msg, wParam, lParam);

    switch (msg) 
    {
    case WM_SIZE: 
    {
        HWND hEdit = pLogConsole->getEditHandle();
        HWND hButton = pLogConsole->getClearButtonHandle();
        HWND hCopyButton = pLogConsole->getCopyButtonHandle();

        WndPosData editPos = pLogConsole->getEditBackgroundSize();

        if (hEdit)
            MoveWindow(hEdit, editPos.x, editPos.y, editPos.width, editPos.height, TRUE);

        WndPosData clearButtonPos = pLogConsole->getClearButtonSize();

        if (hButton)
            MoveWindow(hButton, clearButtonPos.x, clearButtonPos.y, clearButtonPos.width, clearButtonPos.height, TRUE);

		WndPosData copyButtonPos = pLogConsole->getCopyButtonSize();

        if (hCopyButton)
			MoveWindow(hCopyButton, copyButtonPos.x, copyButtonPos.y, copyButtonPos.width, copyButtonPos.height, TRUE);

        return 0;
    }
    case WM_CONSOLE_LOG: 
    {
        HWND hEdit = pLogConsole->getEditHandle();

        std::wstring* text = reinterpret_cast<std::wstring*>(lParam);

        if (hEdit) 
        {
            int len = GetWindowTextLengthW(hEdit);
            SendMessageW(hEdit, EM_SETSEL, len, len);
            SendMessageW(hEdit, EM_REPLACESEL, FALSE, (LPARAM)text->c_str());
            SendMessageW(hEdit, EM_SCROLLCARET, 0, 0);
        }
        delete text;
        return 0;
    }
    case WM_COMMAND:
    {
		int actionID = LOWORD(wParam);

        switch (actionID)
        {
        case ACTION_CLEAR:
        {
            HWND hEdit = pLogConsole->getEditHandle();

            if (hEdit) SendMessageW(hEdit, WM_SETTEXT, 0, (LPARAM)L"");
            break;
        }
        case ACTION_COPY:
        {
            HWND hEdit = pLogConsole->getEditHandle();
            if (!hEdit) break;

            int len = GetWindowTextLengthW(hEdit);
            if (len == 0) break;

            std::wstring text(len + 1, L'\0');
            GetWindowTextW(hEdit, &text[0], len + 1);

            if (OpenClipboard(hwnd))
            {
                EmptyClipboard();
                HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, (len + 1) * sizeof(wchar_t));
                if (hGlob)
                {
                    memcpy(GlobalLock(hGlob), text.c_str(), (len + 1) * sizeof(wchar_t));
                    GlobalUnlock(hGlob);
                    SetClipboardData(CF_UNICODETEXT, hGlob);
                }
                CloseClipboard();
            }

            break;
        }
        default:
            break;
        }

        return 0;
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(255, 255, 255));
        SetBkColor(hdcStatic, RGB(0, 0, 0));
        return (INT_PTR)GetStockObject(BLACK_BRUSH);
    }
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

RConsole::RConsole(const std::wstring& name)
    : m_name(name),
	m_bVisible(false)
{
    m_thread = std::thread([this, name]() { this->threadMain(name); });
}

RConsole::~RConsole()
{
    if (m_hwnd) PostMessage(m_hwnd, WM_CLOSE, 0, 0);

    if (m_hEdit) DestroyWindow(m_hEdit);
    if (m_hClearButton) DestroyWindow(m_hClearButton);
    if (m_hFont) DeleteObject(m_hFont);

    if (m_thread.joinable()) m_thread.join();
}

void RConsole::threadMain(std::wstring title)
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icc);

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = AppLogWindowWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"AppLogWindow";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassW(&wc);

    m_hwnd = CreateWindowExW(
        0, L"AppLogWindow", title.c_str(),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 400,
        nullptr, nullptr, hInstance, nullptr);

    if (!m_hwnd) return;

    HMENU hMenu = GetSystemMenu(m_hwnd, FALSE);
    if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

    WndPosData editPos = getEditBackgroundSize();

    m_hEdit = CreateWindowExW(
        WS_EX_WINDOWEDGE, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY | ES_WANTRETURN,
        editPos.x, editPos.y, editPos.width, editPos.height,
        m_hwnd, nullptr, hInstance, nullptr);

    WndPosData clearButtonPos = getClearButtonSize();

    m_hClearButton = CreateWindowW(
        L"BUTTON", L"Clear",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        clearButtonPos.x, clearButtonPos.y, clearButtonPos.width, clearButtonPos.height,
        m_hwnd, (HMENU)ACTION_CLEAR, hInstance, nullptr);

	WndPosData copyButtonPos = getCopyButtonSize();

    m_hCopyButton = CreateWindowW(
        L"BUTTON", L"Copy",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        copyButtonPos.x, copyButtonPos.y, copyButtonPos.width, copyButtonPos.height,
        m_hwnd, (HMENU)ACTION_COPY, hInstance, nullptr);

    m_hFont = CreateFontW(
        14, 0, 0, 0,
        FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        FIXED_PITCH | FF_MODERN,
        L"Consolas");

    SendMessageW(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, TRUE);

    SetWindowLongPtrW(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
	setVisibility(m_bVisible);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

void RConsole::addLog(const wchar_t* fmt, ...)
{
    wchar_t buffer[1024];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
    va_end(args);

    if (m_hwnd) 
    {
        std::wstring text(buffer);

        for (size_t pos = 0; (pos = text.find(L'\n', pos)) != std::wstring::npos; ++pos)
        {
            if (pos == 0 || text[pos - 1] != L'\r')
            {
                text.replace(pos, 1, L"\r\n");
                pos++;
            }
        }

        auto* copy = new std::wstring(std::move(text));
        PostMessageW(m_hwnd, WM_CONSOLE_LOG, 0, (LPARAM)copy);
    }
}

void RConsole::setVisibility(bool visible)
{
    ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
}

WndPosData RConsole::getEditBackgroundSize()
{
    const int marginX = 5;
	const int marginY = 0;

    RECT rcClient;
    GetClientRect(m_hwnd, &rcClient);

    return WndPosData(rcClient.top + marginX, marginY, (rcClient.right - rcClient.left) - 2 * marginX, (rcClient.bottom - rcClient.top) - 35);
}

WndPosData RConsole::getClearButtonSize()
{
    RECT rcClient;
    GetClientRect(m_hwnd, &rcClient);

    return WndPosData(10, rcClient.bottom - 30, 80, 25);
}

WndPosData RConsole::getCopyButtonSize()
{
	WndPosData clearButtonPos = getClearButtonSize();

	return WndPosData(clearButtonPos.x + clearButtonPos.width + 10, clearButtonPos.y, 80, 25);
}
