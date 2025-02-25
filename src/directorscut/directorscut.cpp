#include <QString>
#include "directorscut.h"

// windows headers
#undef INVALID_HANDLE_VALUE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef PostMessage

#include "materialsystem/materialsystem_config.h"

CDirectorsCutTool* g_pDirectorsCutTool = nullptr;

CDirectorsCutTool::CDirectorsCutTool()
{
}

const char *CDirectorsCutTool::GetToolName()
{
    return DIRECTORSCUT_PRODUCTNAME;
}

bool CDirectorsCutTool::Init()
{
    return true;
}

bool CDirectorsCutTool::ClientInit(CreateInterfaceFn clientFactory)
{
    // Initialize Qt (we waited for engine to be initialized first)
    m_pQt = new CDirectorsCutQt();
    m_pQt->GetMainWindow()->PostInit();
    return true;
}

void CDirectorsCutTool::Shutdown()
{
    SetToolActive(false);
   // Delete Qt handler
    if (m_pQt)
    {
        delete m_pQt;
        m_pQt = nullptr;
    }
}

void CDirectorsCutTool::OnToolActivate()
{
    SetToolActive(true);
}

void CDirectorsCutTool::OnToolDeactivate()
{
    SetToolActive(false);
}

bool CDirectorsCutTool::ServerInit(CreateInterfaceFn serverFactory) {
    return true;
}

void CDirectorsCutTool::ServerShutdown()
{
}

void CDirectorsCutTool::ClientShutdown()
{
}

bool CDirectorsCutTool::CanQuit()
{
    // TODO: Ask to save session document once implemented
    // Ask Qt handler if we can quit
    if (m_pQt)
        return m_pQt->CanQuit();
    return true;
}

void CDirectorsCutTool::PostMessage(HTOOLHANDLE hEntity, KeyValues* message)
{
}

void CDirectorsCutTool::Think(bool finalTick)
{
}

void CDirectorsCutTool::ServerLevelInitPreEntity()
{
}

void CDirectorsCutTool::ServerLevelInitPostEntity()
{
}

void CDirectorsCutTool::ServerLevelShutdownPreEntity()
{
}

void CDirectorsCutTool::ServerLevelShutdownPostEntity()
{
}

void CDirectorsCutTool::ServerFrameUpdatePreEntityThink()
{
}

void CDirectorsCutTool::ServerFrameUpdatePostEntityThink()
{
}

void CDirectorsCutTool::ServerPreClientUpdate()
{
}

void CDirectorsCutTool::ServerPreSetupVisibility()
{
}

const char* CDirectorsCutTool::GetEntityData(const char* pActualEntityData)
{
    return pActualEntityData;
}

void CDirectorsCutTool::ClientLevelInitPreEntity()
{
}

void CDirectorsCutTool::ClientLevelInitPostEntity()
{
}

void CDirectorsCutTool::ClientLevelShutdownPreEntity()
{
}

void CDirectorsCutTool::ClientLevelShutdownPostEntity()
{
}

void CDirectorsCutTool::ClientPreRender()
{
}

void CDirectorsCutTool::ClientPostRender()
{
}

void CDirectorsCutTool::AdjustEngineViewport(int &x, int &y, int &width, int &height)
{
}

bool CDirectorsCutTool::SetupEngineView(Vector &origin, QAngle &angles, float &fov)
{
    return false;
}

bool CDirectorsCutTool::SetupAudioState(AudioState_t &audioState)
{
    return false;
}

bool CDirectorsCutTool::ShouldGameRenderView()
{
    return true;
}

bool CDirectorsCutTool::IsThirdPersonCamera() 
{
    return false;
}

bool CDirectorsCutTool::IsToolRecording()
{
    return false;
}

IMaterialProxy* CDirectorsCutTool::LookupProxy(const char *proxyName)
{
    return NULL;
}

bool CDirectorsCutTool::TrapKey(ButtonCode_t key, bool down) {
    // Toggle tool when KEY_F11 is pressed
    if (key == KEY_F11 && down) {
        ToggleTool();
        return true;
    }
    return false;
}

bool CDirectorsCutTool::GetSoundSpatialization(int iUserData, int guid, SpatializationInfo_t &info)
{
    return false;
}

void CDirectorsCutTool::RenderFrameBegin()
{
}

void CDirectorsCutTool::RenderFrameEnd()
{
}

void CDirectorsCutTool::HostRunFrameBegin()
{
}

void CDirectorsCutTool::HostRunFrameEnd()
{
}

void CDirectorsCutTool::VGui_PreRender(int paintMode)
{
}

void CDirectorsCutTool::VGui_PostRender(int paintMode)
{
}

void CDirectorsCutTool::VGui_PreSimulate()
{
}

void CDirectorsCutTool::VGui_PostSimulate()
{
}

// ===== Our own methods =====

CDirectorsCutQt* CDirectorsCutTool::Qt()
{
    return m_pQt;
}

void CDirectorsCutTool::SetToolActive(bool active)
{
    engine->ClientCmd_Unrestricted("stopsound");

    m_bIsToolActive = active;

    // show or hide game window
    HideOrShowEngineWindow(active);
    
    // Toggle gameui
    if(active) engine->ClientCmd_Unrestricted("gameui_activate");
    else engine->ClientCmd_Unrestricted("gameui_hide");

    // Toggle main window
    if (m_pQt) m_pQt->SetMainWindowVisible(active);
}

void CDirectorsCutTool::ToggleTool()
{
    SetToolActive(!m_bIsToolActive);
}

bool CDirectorsCutTool::IsToolActive()
{
    return m_bIsToolActive;
}

bool CDirectorsCutTool::GetShouldHideEngineWindow()
{
    return m_bShouldHideEngineWindow;
}

void CDirectorsCutTool::SetShouldHideEngineWindow(bool hide)
{
    m_bShouldHideEngineWindow = hide;
}

void CDirectorsCutTool::HideOrShowEngineWindow(bool hide)
{
    m_bIsWindowHidden = !m_bShouldHideEngineWindow && hide;
    if (!m_bIsWindowHidden)
        FocusEngineWindow();
}

void* CDirectorsCutTool::GetEngineWindowHandle()
{
    // FIXME: Don't use windows api and don't try to find a window
    // There can be multiple instances of the engine running
    // set hwnd to the engine window handle
    if (pHWND == (void*)0xFFEEFFEE)
    {
        HWND hwnd = FindWindowA("Valve001", NULL);
        pHWND = (void*)hwnd;
    }
    return pHWND;
}

void CDirectorsCutTool::FocusEngineWindow()
{
    HWND hwnd = (HWND)GetEngineWindowHandle();
    if (hwnd)
    {
        SetForegroundWindow(hwnd);
    }
}
