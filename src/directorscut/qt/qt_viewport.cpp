#include <QString>

#include "directorscut.h"
#include "qt_viewport.h"
#include <vgui/ISurface.h>
#include "vgui_controls/Controls.h"

#include "vguimatsurface/imatsystemsurface.h"
#include "view_shared.h"

CQtViewport::CQtViewport(QWindow* pParent, int iviewportIndex) : CQtMatSysWindow(pParent)
{
    // Run through allocation
    SetViewportIndex(iviewportIndex);
}

CQtViewport::~CQtViewport()
{
	CQtMatSysWindow::~CQtMatSysWindow();
}

int CQtViewport::GetViewportIndex()
{
    return m_iViewportIndex;
}

void CQtViewport::SetViewportIndex(int iviewportIndex)
{
    m_iViewportIndex = iviewportIndex;
}

void CQtViewport::paint()
{
	// shows up as a missing texture... oh well
	IMaterial* pWaitMat = g_pMaterialSystem->FindMaterial("vgui/tools/ifm/ifm_logo", TEXTURE_GROUP_OTHER);

	if (!pWaitMat)
		return;
	
	// By default, let's just make it pink to let em know they need to fill this in.
	g_pMaterialSystem->BeginFrame(0);
	CMatRenderContextPtr pRenderContext(g_pMaterialSystem);

	int w, h, tw, th, cx, cy, mw, mh;
	engine->GetScreenSize(w, h);

	tw = w / 3, th = h / 3;
	cx = (w / 2) - tw;
	cy = (h / 2) - th;

	mw = pWaitMat->GetMappingWidth();
	mh = pWaitMat->GetMappingHeight();

	pRenderContext->Viewport(0, 0, w, h);
	pRenderContext->ClearColor3ub(0x00, 0x00, 0x00);
	pRenderContext->ClearBuffers(true, true);

	pRenderContext->DrawScreenSpaceRectangle(pWaitMat, cx, cy, tw, th, 0, 0, mw - 1, mh - 1, mw, mh);

	g_pMaterialSystem->EndFrame();
	g_pMaterialSystem->SwapBuffers();
}

#include "qt_viewport.h.moc"
