#include <QCloseEvent>
#include "directorscut.h"
#include "qt_mainwindow_menubar.h"
#include "qt_mainwindow.h"
#include "dockwidgets/qt_all_dockwidgets.h"
#include "DockAreaWidget.h"

CQtMainWindow::CQtMainWindow(QWidget* pParent) : QMainWindow(pParent)
{
	// Set up this window's properties
	QIcon icon;
	icon.addFile("tools:/images/directorscut/directorscut_app.png", QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setWindowTitle(QString("%1 [%2]").arg(DIRECTORSCUT_PRODUCTNAME, DIRECTORSCUT_DEVELOPMENT_STAGE));
	resize(1344, 801);

	// Add menu bar and populate it
	m_pMenuBar = new CQtMainWindowMenuBar(this);
	m_pMenuBar->setGeometry(QRect(0, 0, 1344, 27));
	setMenuBar(m_pMenuBar);
	
	// Status bar
	m_pStatusBar = new QStatusBar(this);
	m_pStatusLabel = new QLabel("[ Mem: 0000.00 MB | Game:  0000.0 | fps: 000.0/ 0.000 | Sample:  0000 of 0000 ]");
	m_pStatusBar->addPermanentWidget(m_pStatusLabel);
	setStatusBar(m_pStatusBar);

	// Set up dock manager
	CDockManager::setConfigFlags(CDockManager::DefaultOpaqueConfig);
	CDockManager::setConfigFlag(CDockManager::ActiveTabHasCloseButton, false);
	CDockManager::setConfigFlag(CDockManager::DockAreaHasUndockButton, false);
	CDockManager::setConfigFlag(CDockManager::DockAreaHasTabsMenuButton, false);
	CDockManager::setConfigFlag(CDockManager::DockAreaCloseButtonClosesTab, false);
	CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
	CDockManager::setAutoHideConfigFlag(CDockManager::AutoHideFeatureEnabled, false);
	m_pDockManager = new CDockManager(this);
	//m_pDockManager = new QWidget(this);
	setCentralWidget(m_pDockManager);
}

void CQtMainWindow::PostInit()
{
	// TODO: Use a macro or something so that each tab is
	// added dynamically and not hardcoded like this

	// Create dock widgets
    CQtDockWidget* pAnimationSetEditor = new CQtDockWidget_AnimationSetEditor();
    CQtDockWidget* pConsole = new CQtDockWidget_Console();
    CQtDockWidget* pElementViewer = new CQtDockWidget_ElementViewer();
    CQtDockWidget* pHistory = new CQtDockWidget_History();
    CQtDockWidget* pKeyboardShortcuts = new CQtDockWidget_KeyboardShortcuts();
    CQtDockWidget* pScreencast = new CQtDockWidget_Screencast();
    CQtDockWidget* pScreencastSlides = new CQtDockWidget_ScreencastSlides();
    CQtDockWidget* pScriptEditor = new CQtDockWidget_ScriptEditor();
    CQtDockWidget* pTimeline = new CQtDockWidget_Timeline();
    CQtDockWidget* pPrimaryViewport = new CQtDockWidget_Viewport(0);
    CQtDockWidget* pSecondaryViewport = new CQtDockWidget_Viewport(1);

	// Left side
	CDockWidget* pDockWidget_AnimationSetEditor = new CDockWidget(pAnimationSetEditor->GetTitle());
	pDockWidget_AnimationSetEditor->setWidget(pAnimationSetEditor);
	CDockAreaWidget* pLeftArea = m_pDockManager->addDockWidget(LeftDockWidgetArea, pDockWidget_AnimationSetEditor);
	CDockWidget* pDockWidget_ElementViewer = new CDockWidget(pElementViewer->GetTitle());
	pDockWidget_ElementViewer->setWidget(pElementViewer);
	m_pDockManager->addDockWidget(CenterDockWidgetArea, pDockWidget_ElementViewer, pLeftArea);
	pLeftArea->setCurrentIndex(0);

	// Top right side (large area)
	CDockWidget* pDockWidget_PrimaryViewport = new CDockWidget(pPrimaryViewport->GetTitle());
	pDockWidget_PrimaryViewport->setWidget(pPrimaryViewport);
	CDockAreaWidget* pTopRightArea = m_pDockManager->addDockWidget(RightDockWidgetArea, pDockWidget_PrimaryViewport);
	CDockWidget* pDockWidget_Console = new CDockWidget(pConsole->GetTitle());
	pDockWidget_Console->setWidget(pConsole);
	m_pDockManager->addDockWidget(CenterDockWidgetArea, pDockWidget_Console, pTopRightArea);
	m_pDockManager->setCentralWidget(pDockWidget_PrimaryViewport);
	pTopRightArea->setCurrentIndex(0);

	// Bottom right side
	CDockWidget* pDockWidget_Timeline = new CDockWidget(pTimeline->GetTitle());
	pDockWidget_Timeline->setWidget(pTimeline);
	m_pDockManager->addDockWidget(BottomDockWidgetArea, pDockWidget_Timeline, pTopRightArea);

	// Floating (hidden by default, can be toggled back on in the windows menu)
	CDockWidget* pDockWidget_History = new CDockWidget(pHistory->GetTitle());
	pDockWidget_History->setWidget(pHistory);
	m_pDockManager->addDockWidgetFloating(pDockWidget_History);
	pDockWidget_History->toggleView(false);
	CDockWidget* pDockWidget_KeyboardShortcuts = new CDockWidget(pKeyboardShortcuts->GetTitle());
	pDockWidget_KeyboardShortcuts->setWidget(pKeyboardShortcuts);
	m_pDockManager->addDockWidgetFloating(pDockWidget_KeyboardShortcuts);
	pDockWidget_KeyboardShortcuts->toggleView(false);
	CDockWidget* pDockWidget_Screencast = new CDockWidget(pScreencast->GetTitle());
	pDockWidget_Screencast->setWidget(pScreencast);
	m_pDockManager->addDockWidgetFloating(pDockWidget_Screencast);
	pDockWidget_Screencast->toggleView(false);
	CDockWidget* pDockWidget_ScreencastSlides = new CDockWidget(pScreencastSlides->GetTitle());
	pDockWidget_ScreencastSlides->setWidget(pScreencastSlides);
	m_pDockManager->addDockWidgetFloating(pDockWidget_ScreencastSlides);
	pDockWidget_ScreencastSlides->toggleView(false);
	CDockWidget* pDockWidget_ScriptEditor = new CDockWidget(pScriptEditor->GetTitle());
	pDockWidget_ScriptEditor->setWidget(pScriptEditor);
	m_pDockManager->addDockWidgetFloating(pDockWidget_ScriptEditor);
	pDockWidget_ScriptEditor->toggleView(false);
	CDockWidget* pDockWidget_SecondaryViewport = new CDockWidget(pSecondaryViewport->GetTitle());
	pDockWidget_SecondaryViewport->setWidget(pSecondaryViewport);
	m_pDockManager->addDockWidgetFloating(pDockWidget_SecondaryViewport);
	pDockWidget_SecondaryViewport->toggleView(false);

	// Deallocate temporary dock widgets
	m_pMenuBar->PopulateMenus();
}

CDockManager* CQtMainWindow::GetDockManager()
{
	return m_pDockManager;
}

void CQtMainWindow::closeEvent(QCloseEvent* event)
{
    if (g_pDirectorsCutTool->CanQuit())
    {
		// Tool can quit, hide and prompt user in-engine
		g_pDirectorsCutTool->ToggleTool();
		engine->ClientCmd_Unrestricted("quit prompt");
		// Tab to engine window
		g_pDirectorsCutTool->FocusEngineWindow();
		return;
    }
	event->ignore();
}

#include "qt_mainwindow.h.moc"
