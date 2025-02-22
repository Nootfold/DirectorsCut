#include <QString>
#include "directorscut.h"

// Tier0, Tier1, Tier2, Tier3
#include "tier0/vprof.h"
#include "tier0/icommandline.h"

#include <KeyValues.h>
#include "FileSystem.h"

#include "matsys_controls/matsyscontrols.h"

#include <tier3/tier3.h>

// Steam
#include "steam/steam_api.h"

// Data Cache
#include "datacache/idatacache.h"

// Engine
#include "engine/ienginesound.h"

// Game UI
#include "igameuifuncs.h"

// Input System
#include "inputsystem/iinputsystem.h"

// VGUI
#include <vgui/isurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include <vgui_controls/Panel.h>
#include "vguimatsurface/IMatSystemSurface.h"
#include <vgui/isystem.h>
#include <vgui/ILocalize.h>
#include "vgui_controls/animationcontroller.h"
#include <vgui_controls/Frame.h>
#include <vgui/IInputInternal.h>
#include <vgui_controls/Controls.h>

#include "tooldictionary.h"

using namespace vgui;

// Interface pointers
IVModelRender* modelrender = NULL;
IDataCache* datacache = NULL;
IVModelInfoClient* modelinfo = NULL;
ISpatialPartition* partition = NULL;
IFileSystem* filesystem = NULL;
IEngineSound* enginesound = NULL;
IUniformRandomStream* random = NULL;
static CGaussianRandomStream s_GaussianRandomStream;
CGaussianRandomStream* randomgaussian = &s_GaussianRandomStream;
IGameUIFuncs* gameuifuncs = NULL;
IInputSystem* inputsystem = NULL;
IUploadGameStats* gamestatsuploader = NULL;
ISoundEmitterSystemBase* soundemitterbase = NULL;
static CGlobalVarsBase dummyvars(true);
CGlobalVarsBase* gpGlobals = &dummyvars;
CSysModule* ProcShaderModule = NULL;
IVRenderView* render = NULL;
IVEngineClient* engine = NULL;
IEngineTool* enginetools = NULL;
IEngineVGui* enginevgui = NULL;
IMDLCache* g_pMDLCache = NULL;

bool CToolDictionary::Connect(CreateInterfaceFn factory)
{
    // Connect all interfaces
    MathLib_Init();
    ConnectTier1Libraries(&factory, 1);
    ConnectTier2Libraries(&factory, 1);
    ConnectTier3Libraries(&factory, 1);

    // Factories
    modelrender = (IVModelRender*)factory(VENGINE_HUDMODEL_INTERFACE_VERSION, NULL);
    if (!modelrender)
        return false;
    datacache = (IDataCache*)factory(DATACACHE_INTERFACE_VERSION, NULL);
    if (!datacache)
        return false;
    mdlcache = (IMDLCache*)factory(MDLCACHE_INTERFACE_VERSION, NULL);
    if (!mdlcache)
        return false;
    modelinfo = (IVModelInfoClient*)factory(VMODELINFO_CLIENT_INTERFACE_VERSION, NULL);
    if (!modelinfo)
        return false;
    g_pMaterialSystem = (IMaterialSystem*)factory(MATERIAL_SYSTEM_INTERFACE_VERSION, NULL);
    if (!g_pMaterialSystem)
        return false;
    g_pStudioRender = (IStudioRender*)factory(STUDIO_RENDER_INTERFACE_VERSION, NULL);
    if (!g_pStudioRender)
        return false;
    enginesound = (IEngineSound*)factory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL);
    if (!enginesound)
        return false;
    filesystem = (IFileSystem*)factory(FILESYSTEM_INTERFACE_VERSION, NULL);
    if (!filesystem)
        return false;
    random = (IUniformRandomStream*)factory(VENGINE_CLIENT_RANDOM_INTERFACE_VERSION, NULL);
    if (!random)
        return false;
    gameuifuncs = (IGameUIFuncs*)factory(VENGINE_GAMEUIFUNCS_VERSION, NULL);
    if (!gameuifuncs)
        return false;
    inputsystem = (IInputSystem*)factory(INPUTSYSTEM_INTERFACE_VERSION, NULL);
    if (!inputsystem)
        return false;
    if (!g_pMaterialSystemHardwareConfig)
        return false;
    render = (IVRenderView*)factory(VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL);
    if (!render)
        return false;
    engine = (IVEngineClient*)factory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
    if (!engine)
        return false;
    enginevgui = (IEngineVGui*)factory(VENGINE_VGUI_VERSION, NULL);
    if (!enginevgui)
        return false;
    enginetools = (IEngineTool*)factory(VENGINETOOL_INTERFACE_VERSION, NULL);
    if (!enginetools)
        return false;

    // Other misc. interfaces
    s_GaussianRandomStream.AttachToStream(random);
    ConVar_Register(FCVAR_CLIENTDLL);

    // VGUI
    if (!vgui::VGui_InitInterfacesList("directorscut", &factory, 1))
        return false;
    if (g_pVGuiSurface == NULL ||
        g_pMatSystemSurface == NULL ||
        g_pVGuiInput == NULL ||
        g_pVGui == NULL ||
        g_pVGuiPanel == NULL ||
        g_pVGuiLocalize == NULL ||
        g_pVGuiSchemeManager == NULL ||
        g_pVGuiSystem == NULL)
        return false;
    if (!vgui::VGui_InitMatSysInterfacesList("directorscut", &factory, 1))
        return false;
        
    return true;
}

void CToolDictionary::Disconnect()
{
    // Disconnect all interfaces
    g_pMaterialSystem = NULL;
    g_pStudioRender = NULL;
    mdlcache = NULL;
    modelinfo = NULL;
    datacache = NULL;
    modelrender = NULL;
    enginesound = NULL;
    filesystem = NULL;
    random = NULL;
    gameuifuncs = NULL;
    inputsystem = NULL;
    g_pMaterialSystemHardwareConfig = NULL;
    render = NULL;
    engine = NULL;
    enginevgui = NULL;
    enginetools = NULL;

    // Other misc. interfaces
    ConVar_Unregister();
    s_GaussianRandomStream = NULL;
    if (ProcShaderModule)
    {
        Sys_UnloadModule(ProcShaderModule);
        ProcShaderModule = NULL;
    }

    // VGUI
    if (g_pVGui)
    {
        g_pVGui->Shutdown();
        g_pVGui = NULL;
    }
    g_pVGuiSurface = NULL;
    g_pMatSystemSurface = NULL;
    g_pVGuiInput = NULL;
    g_pVGuiPanel = NULL;
    g_pVGuiLocalize = NULL;
    g_pVGuiSchemeManager = NULL;
    g_pVGuiSystem = NULL;

    ConVar_Unregister();
    DisconnectTier3Libraries();
    DisconnectTier2Libraries();
    DisconnectTier1Libraries();
}

void* CToolDictionary::QueryInterface(const char* pInterfaceName)
{
    CreateInterfaceFn factory = Sys_GetFactoryThis();
    return factory(pInterfaceName, NULL);
}

InitReturnVal_t CToolDictionary::Init()
{
    return INIT_OK;
}

void CToolDictionary::Shutdown()
{
    // Delete singleton instance if available
    if (g_pDirectorsCutTool)
    {
        delete g_pDirectorsCutTool;
        g_pDirectorsCutTool = nullptr;
    }
}

void CToolDictionary::CreateTools()
{
    // Create Director's Cut singleton instance
    g_pDirectorsCutTool = new CDirectorsCutTool();
}

int CToolDictionary::GetToolCount() const
{
    // Only one tool is available
    return 1;
}

IToolSystem* CToolDictionary::GetTool(int index)
{
    // No other tools are available, so return the Director's Cut tool
    if (index == 0)
    {
        return g_pDirectorsCutTool;
    }
    return nullptr;
}
