#pragma once

#include "toolframework/itoolsystem.h"
#include "tooldictionary.h"
#include "soundinfo.h"
#include "keyvalues.h"
#include "cdll_int.h"
#include <materialsystem/imaterialproxyfactory.h>

class DirectorsCutTool : public IToolSystem
{
public:
    DirectorsCutTool();
    virtual const char* GetToolName();
    virtual bool Init();
    virtual void Shutdown();
    virtual bool ClientInit(CreateInterfaceFn clientFactory);
    virtual void OnToolActivate();
    virtual void OnToolDeactivate();
    virtual bool ServerInit(CreateInterfaceFn serverFactory);
    virtual void ServerShutdown();
    virtual void ClientShutdown();
    virtual bool CanQuit();
    virtual void PostMessage(HTOOLHANDLE hEntity, KeyValues* message);
    virtual void Think(bool finalTick);
    virtual void ServerLevelInitPreEntity();
    virtual void ServerLevelInitPostEntity();
    virtual void ServerLevelShutdownPreEntity();
    virtual void ServerLevelShutdownPostEntity();
    virtual void ServerFrameUpdatePreEntityThink();
    virtual void ServerFrameUpdatePostEntityThink();
    virtual void ServerPreClientUpdate();
    virtual void ServerPreSetupVisibility();
    virtual const char* GetEntityData(const char* pActualEntityData);
    virtual void ClientLevelInitPreEntity();
    virtual void ClientLevelInitPostEntity();
    virtual void ClientLevelShutdownPreEntity();
    virtual void ClientLevelShutdownPostEntity();
    virtual void ClientPreRender();
    virtual void ClientPostRender();
    virtual void AdjustEngineViewport(int &x, int &y, int &width, int &height);
    virtual bool SetupEngineView(Vector &origin, QAngle &angles, float &fov);
    virtual bool SetupAudioState(AudioState_t &audioState);
    virtual bool ShouldGameRenderView();
    virtual bool IsThirdPersonCamera();
    virtual bool IsToolRecording();
    virtual IMaterialProxy* LookupProxy(const char *proxyName);
    virtual bool TrapKey(ButtonCode_t key, bool down);
    virtual bool GetSoundSpatialization(int iUserData, int guid, SpatializationInfo_t &info);
    virtual void RenderFrameBegin();
    virtual void RenderFrameEnd();
    virtual void HostRunFrameBegin();
    virtual void HostRunFrameEnd();
    virtual void VGui_PreRender(int paintMode);
    virtual void VGui_PostRender(int paintMode);
    virtual void VGui_PreSimulate();
    virtual void VGui_PostSimulate();
};
