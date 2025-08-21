#include <windows.h>
#include <string>
#include <stdexcept>
#include <mutex>

struct WndPosData
{
    int x;
    int y;
    int width;
    int height;
};

class RConsole
{
public:
    RConsole() {}
    RConsole(const std::wstring& name);
    ~RConsole();

    void log(const wchar_t* fmt, ...);

    void setVisibility(bool visible);

	HWND getWindowHandle() const { return m_hwnd; }
	HWND getEditHandle() const { return m_hEdit; }
    HWND getClearButtonHandle() const { return m_hClearButton; }
	HWND getCopyButtonHandle() const { return m_hCopyButton; }

    WndPosData getEditBackgroundSize();
    WndPosData getClearButtonSize();
    WndPosData getCopyButtonSize();
private:
    HWND m_hwnd = nullptr;
    std::wstring m_name;
    std::thread m_thread;
	std::mutex m_mutex;
	bool m_bVisible = false;
	HWND m_hEdit = nullptr;
	HWND m_hClearButton = nullptr;
	HWND m_hCopyButton = nullptr;
	HFONT m_hFont = nullptr;

    void threadMain(std::wstring title);
};