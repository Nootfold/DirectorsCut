#include <QCloseEvent>
#include "directorscut.h"
#include "qt_mainwindow_menubar.h"
#include "qt_mainwindow.h"

CQtMainWindow::CQtMainWindow(QWidget* pParent) : QMainWindow(pParent)
{
	// Set up this window's properties
	QIcon icon;
	icon.addFile("tools:/images/directorscut/directorscut_app.png", QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setWindowTitle("Director's Cut [Pre-Alpha]");
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
	
	QLabel* l = new QLabel();
	l->setWordWrap(true);
	l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	l->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ");
	ads::CDockWidget* DockWidget = new ads::CDockWidget("Label 1");
	DockWidget->setWidget(l);
	m_pMenuBar->addAction(DockWidget->toggleViewAction());
	m_pDockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
	
	QLabel* l2 = new QLabel();
	l2->setWordWrap(true);
	l2->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	l2->setText("Label 2! ");
	ads::CDockWidget* DockWidget2 = new ads::CDockWidget("Label 2");
	DockWidget2->setWidget(l2);
	m_pMenuBar->addAction(DockWidget2->toggleViewAction());
	m_pDockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget2);
	
	QLabel* l3 = new QLabel();
	l3->setWordWrap(true);
	l3->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	l3->setText("Label 3! ");
	ads::CDockWidget* DockWidget3 = new ads::CDockWidget("Label 3");
	DockWidget3->setWidget(l3);
	m_pMenuBar->addAction(DockWidget3->toggleViewAction());
	m_pDockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget3);
}

void CQtMainWindow::populateMenus()
{
	// Pass-through to menu bar
	m_pMenuBar->populateMenus();
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
