Hello ragezone. Our community may be dead but that doesn't stop my curiosity to develop new features for gunz. Today I release Webview2 for Gunz. It's not new but it's a platform for you to develop amazingly powerful features for this old game. For me it's quite convenient to develop new features via PHP and then the client just shows it to the player to experience without touching the source code too much (really a headache ^^~).

Video where you will see how powerful Webview2 is

[Video](https://streamable.com/l8pz5o)

I added Webview2 to both my Launcher and Gunz sources. This code is very basic for you to start with, if you improve it please share it here for everyone to refer to.

Tutorial ^^~

1. Gunz Project > Manage NuGet packages

2. Find Microsoft.Web.WebView2 and Install
3. Code
Create new WebViewOverlay.cpp in your project Gunz

```
#include "stdafx.h"
#include <windows.h>
#include <wrl.h>
#include <WebView2.h>
#include <string>

using namespace Microsoft::WRL;

HWND g_hWebWnd = nullptr;
ComPtr<ICoreWebView2Controller> g_webController;
ComPtr<ICoreWebView2> g_webView;

std::wstring ToWide(const char* str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    std::wstring wstr(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str, -1, &wstr[0], len);
    return wstr;
}

LRESULT CALLBACK WebProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_NCHITTEST:
    {
        LRESULT hit = DefWindowProc(hWnd, msg, wParam, lParam);
        if (hit == HTCAPTION)
            return hit;
        return HTCLIENT;
    }

    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
    {
        if (g_webController) g_webController->Close();
        g_webController = nullptr;
        g_webView = nullptr;
        g_hWebWnd = nullptr;

        while (ShowCursor(FALSE) >= 0);

        OutputDebugStringA("[WebView2] Window destroyed, cursor restored.\n");
        return 0;
    }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void ZShowWebPage(const char* url)
{
    if (g_hWebWnd)
    {
        SetForegroundWindow(g_hWebWnd);
        return;
    }

    HINSTANCE hInst = GetModuleHandle(NULL);
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WebProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "GUNZ_WEBVIEW";
    RegisterClassA(&wc);

    int width = 900, height = 600;
    int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    g_hWebWnd = CreateWindowExA(
        WS_EX_APPWINDOW,
        wc.lpszClassName,
        "Gunz WebViewer",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        x, y, width, height,
        NULL, NULL, hInst, NULL);

    if (!g_hWebWnd)
        return;

    std::wstring wurl = ToWide(url);
    while (ShowCursor(TRUE) < 0);

    char szCachePath[MAX_PATH];
    GetModuleFileNameA(NULL, szCachePath, MAX_PATH);
    char* p = strrchr(szCachePath, '\\');
    if (p) *p = '\0';
    strcat_s(szCachePath, "\\WebView2");

    CreateDirectoryA(szCachePath, NULL);

    std::wstring wCachePath = std::wstring(szCachePath, szCachePath + strlen(szCachePath));

    CreateCoreWebView2EnvironmentWithOptions(
        nullptr,
        wCachePath.c_str(),
        nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [wurl](HRESULT result, ICoreWebView2Environment* env) -> HRESULT

            {
                env->CreateCoreWebView2Controller(g_hWebWnd,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [wurl](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT
                        {
                            if (!controller) return E_FAIL;

                            g_webController = controller;
                            g_webController->get_CoreWebView2(&g_webView);

                            ComPtr<ICoreWebView2Settings> settings;
                            if (SUCCEEDED(g_webView->get_Settings(&settings)))
                            {
                                settings->put_AreDefaultContextMenusEnabled(FALSE);
                                settings->put_AreDevToolsEnabled(FALSE);
                            }

                            RECT bounds;
                            GetClientRect(g_hWebWnd, &bounds);
                            g_webController->put_Bounds(bounds);

                            g_webView->Navigate(wurl.c_str());
                            return S_OK;
                        }).Get());
                return S_OK;
            }).Get());
}
```

ZGameInterface.h
find
public: ZGameInterface(const char* szName=NULL, MWidget* pParent=NULL, MListener* pListener=NULL);
add

```
void ToggleWebView(const char* pszURL = NULL);
```

ZGameInterface.cpp

```
void ZGameInterface::ToggleWebView(const char* pszURL)
{

    if (g_hWebWnd && IsWindow(g_hWebWnd))
    {
        mlog("WebView window active → closing it.\n");
        DestroyWindow(g_hWebWnd);
        g_hWebWnd = nullptr;

        while (ShowCursor(FALSE) >= 0);
        return;
    }

    const char* finalURL = pszURL ? pszURL : "PUT YOUR LINK IN HERE LIKE THIS https://google.com";

//my example
//const char* finalURL = pszURL ? pszURL : "https://yourgunz.com/feature/battlepass/index.php";

    mlog("Opening WebView at: %s\n", finalURL);
    ZShowWebPage(finalURL);
}
```

find
bool ZGameInterface::InitInterfaceListener()
add

```
SetListenerWidget("OpenWebViewButton", ZGetOpenWebViewListener());
```

ZInterfaceListener.h
add

```
DECLARE_LISTENER(ZGetOpenWebViewListener)
```

ZInterfaceListener.cpp
add

```
BEGIN_IMPLEMENT_LISTENER(ZGetOpenWebViewListener, MBTN_CLK_MSG)
ZGetGameInterface()->ToggleWebView("");
END_IMPLEMENT_LISTENER()
```

Client Interface/default/Lobby.xml
add

```
    <BMBUTTON item="OpenWebViewButton" parent="Lobby">
        <BUTTONLOOK>NormalBmButtonLook</BUTTONLOOK>
        <BOUNDS>
            <X>318</X>
            <Y>565</Y>
            <W>130</W>
            <H>25</H>
        </BOUNDS>
        <STRETCH/>
        <BITMAP type="up">web_off.png</BITMAP> <!---Custom your img or use BUTTON TEXT-->
        <BITMAP type="over">web_on.png</BITMAP>
        <BITMAP type="down">web_on.png</BITMAP>
    </BMBUTTON>
```


















