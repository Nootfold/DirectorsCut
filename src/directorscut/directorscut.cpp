#include <QApplication>
#include <QDir>
#include <QFile>

#include "app.h"

#include "qt_ui/ui.h"

#include "directorscut.h"

QApplication* g_pDirectorsCutApp = nullptr;
CMainWindow* m_pMainWindow;

// Currently blank, but might be worth filling in if you need mat proxies
class CMaterialProxyFactory : public IMaterialProxyFactory
{
public:
	virtual IMaterialProxy* CreateProxy(const char* proxyName) { return nullptr; }
	virtual void DeleteProxy(IMaterialProxy* pProxy) { }
};
static CMaterialProxyFactory s_materialProxyFactory;


DirectorsCutTool::DirectorsCutTool()
{
}

const char *DirectorsCutTool::GetToolName()
{
    return "Director's Cut";
}

bool DirectorsCutTool::Init()
{
    return true;
}

bool DirectorsCutTool::ClientInit(CreateInterfaceFn clientFactory)
{
    // get tool assets directory
    QString dir = "bin/directorscut";

    // set library paths
    QCoreApplication::addLibraryPath(dir);

    // define qdir!
    QDir::addSearchPath("tools", dir);

    // initialize QApplication and set it
    // this is required because qt will shut down if there is no QApplication instance
    int argc = 0;
	g_pDirectorsCutApp = new QApplication(argc, nullptr);

    // load dxfm.qss as the stylesheet
    QFile file("tools:stylesheets/directorscut.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    g_pDirectorsCutApp->setStyleSheet(styleSheet);
    return true;
}

void DirectorsCutTool::Shutdown()
{
}

void DirectorsCutTool::OnToolActivate()
{
    if(!m_pMainWindow)
        m_pMainWindow = new CMainWindow(nullptr);
    m_pMainWindow->show();
}

void DirectorsCutTool::OnToolDeactivate()
{
}

bool DirectorsCutTool::ServerInit(CreateInterfaceFn serverFactory) {
    return true;
}

void DirectorsCutTool::ServerShutdown()
{
}

void DirectorsCutTool::ClientShutdown()
{
}

bool DirectorsCutTool::CanQuit() {
    return true;
}

void DirectorsCutTool::PostMessage(HTOOLHANDLE hEntity, KeyValues* message)
{
}

void DirectorsCutTool::Think(bool finalTick)
{
}

void DirectorsCutTool::ServerLevelInitPreEntity()
{
}

void DirectorsCutTool::ServerLevelInitPostEntity()
{
}

void DirectorsCutTool::ServerLevelShutdownPreEntity()
{
}

void DirectorsCutTool::ServerLevelShutdownPostEntity()
{
}

void DirectorsCutTool::ServerFrameUpdatePreEntityThink()
{
}

void DirectorsCutTool::ServerFrameUpdatePostEntityThink()
{
}

void DirectorsCutTool::ServerPreClientUpdate()
{
}

void DirectorsCutTool::ServerPreSetupVisibility()
{
}

const char* DirectorsCutTool::GetEntityData(const char* pActualEntityData)
{
    return pActualEntityData;
}

void DirectorsCutTool::ClientLevelInitPreEntity()
{
}

void DirectorsCutTool::ClientLevelInitPostEntity()
{
}

void DirectorsCutTool::ClientLevelShutdownPreEntity()
{
}

void DirectorsCutTool::ClientLevelShutdownPostEntity()
{
}

void DirectorsCutTool::ClientPreRender()
{
}

void DirectorsCutTool::ClientPostRender()
{
}

void DirectorsCutTool::AdjustEngineViewport(int &x, int &y, int &width, int &height)
{
}

bool DirectorsCutTool::SetupEngineView(Vector &origin, QAngle &angles, float &fov)
{
    return false;
}

bool DirectorsCutTool::SetupAudioState(AudioState_t &audioState)
{
    return false;
}

bool DirectorsCutTool::ShouldGameRenderView()
{
    return true;
}

bool DirectorsCutTool::IsThirdPersonCamera() 
{
    return false;
}

bool DirectorsCutTool::IsToolRecording()
{
    return false;
}

IMaterialProxy* DirectorsCutTool::LookupProxy(const char *proxyName)
{
    return NULL;
}

bool DirectorsCutTool::TrapKey(ButtonCode_t key, bool down) {
    return false;
}

bool DirectorsCutTool::GetSoundSpatialization(int iUserData, int guid, SpatializationInfo_t &info)
{
    return false;
}

void DirectorsCutTool::RenderFrameBegin()
{
}

void DirectorsCutTool::RenderFrameEnd()
{
}

void DirectorsCutTool::HostRunFrameBegin()
{
}

void DirectorsCutTool::HostRunFrameEnd()
{
}

void DirectorsCutTool::VGui_PreRender(int paintMode)
{
}

void DirectorsCutTool::VGui_PostRender(int paintMode)
{
}

void DirectorsCutTool::VGui_PreSimulate()
{
}

void DirectorsCutTool::VGui_PostSimulate()
{
}
