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

	// Main widget
	m_pMainWidget = new QWidget(this);
	setCentralWidget(m_pMainWidget);
}

void CQtMainWindow::closeEvent(QCloseEvent* event)
{
    if (g_pDirectorsCutTool->CanQuit())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

#include "qt_mainwindow.h.moc"
