#include <qpa/qplatformwindow.h>

// Source tends to do funny stuff with defines. Let's just include it last just to be safe.
#include <tier2/tier2.h>
#include <materialsystem/imaterialsystem.h>
#include <VGuiMatSurface/IMatSystemSurface.h>
#include <materialsystem/materialsystem_config.h>
#include <materialsystem/itexture.h>

#include "qt_matsyswindow.h"
#include "directorscut.h"

// Main Window

CQtMatSysWindow::CQtMatSysWindow(QWindow* pParent) : QWindow(pParent)
{
	g_pDirectorsCutTool->Qt()->AddManagedView(this);
}

CQtMatSysWindow::~CQtMatSysWindow()
{
	if(m_bRemoving)
		return;
	m_bRemoving = true;
	g_pDirectorsCutTool->Qt()->RemoveManagedView(this);
}

void CQtMatSysWindow::paint()
{
	// By default, let's just make it pink to let em know they need to fill this in.
	g_pMaterialSystem->BeginFrame(0);

	CMatRenderContextPtr ctx(g_pMaterialSystem);
	ctx->Viewport(0, 0, width(), height());
	ctx->ClearColor3ub(0xFF, 0x00, 0xFF);
	ctx->ClearBuffers(true, false);
	ctx.SafeRelease();

	g_pMaterialSystem->EndFrame();
	g_pMaterialSystem->SwapBuffers();
}

#include "qt_matsyswindow.h.moc"