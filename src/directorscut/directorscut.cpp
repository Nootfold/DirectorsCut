#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include "directorscut.h"

CDirectorsCutTool* g_pDirectorsCutTool = nullptr;

CDirectorsCutTool::CDirectorsCutTool()
{
}

const char *CDirectorsCutTool::GetToolName()
{
    return "Director's Cut";
}

bool CDirectorsCutTool::Init()
{
    return true;
}

bool CDirectorsCutTool::ClientInit(CreateInterfaceFn clientFactory)
{
    // Run on client init because we need to wait for engine to be initialized

    // Initialize library and search paths
    #ifdef PLATFORM_64BITS
    QString libraryPath = "bin/directorscut/x64";
    #else
    QString libraryPath = "bin/directorscut";
    #endif
    QCoreApplication::addLibraryPath(libraryPath);
    QString searchPath = "bin/directorscut";
    QDir::addSearchPath("tools", searchPath);

    // Create application
    int argc = 0;
    m_pApplication = new QApplication(argc, nullptr);
    QFile file("tools:stylesheets/directorscut.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        m_pApplication->setStyleSheet(styleSheet);
    } else {
        // User-friendly error message
        QMessageBox::critical(nullptr, "Error", "Failed to load stylesheet. Director's Cut will use the default Qt stylesheet.");
    }

    // Create main window
    m_pMainWindow = new CQtMainWindow(nullptr);
    m_pMainWindow->populateMenus();
    return true;
}

void CDirectorsCutTool::Shutdown()
{
    // Destroy members and shut down Qt
    SetToolActive(false);
    if (m_pMainWindow)
    {
        m_pMainWindow->close();
        delete m_pMainWindow;
        m_pMainWindow = nullptr;
    }
    if (m_pApplication)
    {
        m_pApplication->quit();
        delete m_pApplication;
        m_pApplication = nullptr;
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

bool CDirectorsCutTool::CanQuit() {
    // TODO: Ask to save session document once implemented
    // Only allow the tool to quit if no modal dialogs are open
    return QApplication::activeModalWidget() == nullptr;
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

CQtMainWindow* CDirectorsCutTool::GetMainWindow()
{
    return m_pMainWindow;
}

void CDirectorsCutTool::SetToolActive(bool active)
{
    engine->ClientCmd_Unrestricted("stopsound");

    bIsToolActive = active;

    // show or hide game window
    HideOrShowEngineWindow(active);

    if(active)
    {
        engine->ClientCmd_Unrestricted("gameui_activate");
        m_pMainWindow->show();
        m_pMainWindow->activateWindow();
    }
    else
    {
        engine->ClientCmd_Unrestricted("gameui_hide");
        m_pMainWindow->hide();
    }
}

void CDirectorsCutTool::ToggleTool()
{
    SetToolActive(!bIsToolActive);
}

bool CDirectorsCutTool::IsToolActive()
{
    return bIsToolActive;
}

bool CDirectorsCutTool::GetShouldHideEngineWindow()
{
    return bShouldHideEngineWindow;
}

void CDirectorsCutTool::SetShouldHideEngineWindow(bool hide)
{
    bShouldHideEngineWindow = hide;
}

void CDirectorsCutTool::HideOrShowEngineWindow(bool hide)
{
    if(!bShouldHideEngineWindow)
        hide = false;
    bIsWindowHidden = hide;
}
