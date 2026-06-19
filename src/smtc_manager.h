#pragma once
#include <windows.h>
#include <string>
#include <functional>

// SMTC (System Media Transport Controls) 管理器
// 让 AirPlay 音频流集成到 Windows 系统媒体控件（任务栏音量区/锁屏）
class SMTCManager {
public:
    SMTCManager();
    ~SMTCManager();

    // 初始化：绑定到主窗口，注册 SMTC
    bool initialize(HWND window);

    // 更新播放状态
    void setPlaybackState(bool playing);

    // 更新曲目信息
    void setTrackInfo(const std::wstring& title, 
                      const std::wstring& artist = L"",
                      const std::wstring& album = L"");

    // 清理资源
    void cleanup();

    // SMTC 按钮动作回调
    enum Action { ActionPlay = 0, ActionPause = 1, ActionToggle = 2 };
    using ButtonCallback = std::function<void(Action action)>;
    void setButtonCallback(ButtonCallback cb);

    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized = false;
    bool m_roInitialized = false;
    HWND m_window = nullptr;
    void* m_controls = nullptr;       // ISystemMediaTransportControls*
    void* m_events_token = nullptr;   // EventRegistrationToken*
    ButtonCallback m_callback;

    // 内部清理
    void unregisterEvents();
    void releaseInterfaces();
};
