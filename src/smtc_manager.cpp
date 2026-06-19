#include "smtc_manager.h"

// SMTC 需要 Windows SDK 的 WinRT 头文件，仅在 MSVC 下可用
// MinGW (GCC) 下自动降级为空操作
#ifdef _MSC_VER

#include <roapi.h>
#include <windows.media.h>
#include <windows.media.systemmediatransportcontrolsinterop.h>

#include <wrl.h>
#include <wrl/event.h>

using namespace ABI::Windows::Media;
using namespace ABI::Windows::Media::SystemMediaTransportControls;
using namespace Microsoft::WRL;

// ==================== SMTC 按钮事件处理器 ====================
class SMTCButtonHandler : 
    public RuntimeClass<RuntimeClassFlags<ClassicCom>,
                        FtmBase,
                        ISystemMediaTransportControlsButtonPressedEventHandler> {
public:
    SMTCButtonHandler(SMTCManager::ButtonCallback cb) : m_callback(cb) {}

    IFACEMETHODIMP Invoke(
        ISystemMediaTransportControls* /*sender*/,
        ISystemMediaTransportControlsButtonPressedEventArgs* args) override {

        if (!args || !m_callback) return S_OK;

        SystemMediaTransportControlsButton button;
        HRESULT hr = args->get_Button(&button);
        if (FAILED(hr)) return S_OK;

        switch (button) {
        case SystemMediaTransportControlsButton_Play:
            m_callback(SMTCManager::ActionPlay);
            break;
        case SystemMediaTransportControlsButton_Pause:
            m_callback(SMTCManager::ActionPause);
            break;
        case SystemMediaTransportControlsButton_PlayPause:
            m_callback(SMTCManager::ActionToggle);
            break;
        default:
            break;
        }
        return S_OK;
    }

private:
    SMTCManager::ButtonCallback m_callback;
};

SMTCManager::SMTCManager()
    : m_initialized(false)
    , m_roInitialized(false)
    , m_window(nullptr)
    , m_controls(nullptr)
    , m_events_token(nullptr) {
}

SMTCManager::~SMTCManager() {
    cleanup();
}

bool SMTCManager::initialize(HWND window) {
    if (m_initialized) return true;
    if (!window) return false;

    m_window = window;

    HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) return false;
    m_roInitialized = true;

    ComPtr<ISystemMediaTransportControlsInterop> interop;
    hr = RoGetActivationFactory(
        HStringReference(RuntimeClass_Windows_Media_SystemMediaTransportControls).Get(),
        IID_PPV_ARGS(&interop));
    if (FAILED(hr)) return false;

    ISystemMediaTransportControls* controls = nullptr;
    hr = interop->GetForWindow(m_window, IID_PPV_ARGS(&controls));
    if (FAILED(hr) || !controls) return false;
    m_controls = controls;

    controls->put_IsEnabled(true);
    controls->put_IsPlayEnabled(true);
    controls->put_IsPauseEnabled(true);
    controls->put_IsNextEnabled(false);
    controls->put_IsPreviousEnabled(false);

    auto handler = Make<SMTCButtonHandler>(m_callback);
    if (handler) {
        EventRegistrationToken token;
        hr = controls->add_ButtonPressed(handler.Get(), &token);
        if (SUCCEEDED(hr)) {
            m_events_token = new EventRegistrationToken(token);
        }
    }

    m_initialized = true;
    return true;
}

void SMTCManager::setPlaybackState(bool playing) {
    if (!m_initialized || !m_controls) return;
    auto controls = static_cast<ISystemMediaTransportControls*>(m_controls);
    controls->put_PlaybackStatus(playing
        ? SystemMediaTransportControlsPlaybackStatusPlaying
        : SystemMediaTransportControlsPlaybackStatusPaused);
}

void SMTCManager::setTrackInfo(const std::wstring& title,
                                const std::wstring& artist,
                                const std::wstring& album) {
    if (!m_initialized || !m_controls) return;
    auto controls = static_cast<ISystemMediaTransportControls*>(m_controls);

    ISystemMediaTransportControlsDisplayUpdater* updater = nullptr;
    HRESULT hr = controls->get_DisplayUpdater(&updater);
    if (FAILED(hr) || !updater) return;

    updater->put_Type(MediaPlaybackType::MediaPlaybackType_Music);

    IMusicDisplayProperties* musicProps = nullptr;
    hr = updater->get_MusicProperties(&musicProps);
    if (SUCCEEDED(hr) && musicProps) {
        if (!title.empty()) musicProps->put_Title(HStringReference(title.c_str()).Get());
        if (!artist.empty()) musicProps->put_Artist(HStringReference(artist.c_str()).Get());
        if (!album.empty()) musicProps->put_AlbumTitle(HStringReference(album.c_str()).Get());
        musicProps->Release();
    }
    updater->Update();
    updater->Release();
}

void SMTCManager::setButtonCallback(ButtonCallback cb) { m_callback = cb; }

void SMTCManager::unregisterEvents() {
    if (m_controls && m_events_token) {
        auto controls = static_cast<ISystemMediaTransportControls*>(m_controls);
        controls->remove_ButtonPressed(*static_cast<EventRegistrationToken*>(m_events_token));
    }
    delete static_cast<EventRegistrationToken*>(m_events_token);
    m_events_token = nullptr;
}

void SMTCManager::releaseInterfaces() {
    if (m_controls) {
        static_cast<ISystemMediaTransportControls*>(m_controls)->Release();
        m_controls = nullptr;
    }
}

void SMTCManager::cleanup() {
    unregisterEvents();
    releaseInterfaces();
    m_initialized = false;
    m_window = nullptr;
    if (m_roInitialized) { RoUninitialize(); m_roInitialized = false; }
}

#else

SMTCManager::SMTCManager() : m_initialized(false), m_roInitialized(false), m_window(nullptr), m_controls(nullptr), m_events_token(nullptr) {}
SMTCManager::~SMTCManager() { cleanup(); }
bool SMTCManager::initialize(HWND) { return false; }
void SMTCManager::setPlaybackState(bool) {}
void SMTCManager::setTrackInfo(const std::wstring&, const std::wstring&, const std::wstring&) {}
void SMTCManager::setButtonCallback(ButtonCallback) {}
void SMTCManager::cleanup() { m_initialized = false; }
void SMTCManager::unregisterEvents() {}
void SMTCManager::releaseInterfaces() {}

#endif
