#include <QPixmap>
#include <QSlider>
#include <QDialog>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMessageBox>
#include <QWidget>
#include <QDockWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStatusBar>

#include "aboutdialog.h"

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>

#include "ui.h"

#include "app.h"

// Main Window
// Embeds two matsyswindows into the same window, using container widgers

CMainWindow::CMainWindow(QWidget* pParent) : QMainWindow(pParent)
{
	// Set up this window's properties
	QIcon icon;
	icon.addFile("tools:/images/directorscut/directorscut_app.png", QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setWindowTitle("Director's Cut [Pre-Alpha]");
	resize(1344, 801);

	// Add menu bar and populate it
	QMenuBar* menubar = new QMenuBar(this);
	menubar->setGeometry(QRect(0, 0, 1344, 27));
	setMenuBar(menubar);

	QMenu* menuFile = new QMenu("File", menubar);
	QAction* actionQuit = new QAction("Quit", menuFile);
	connect(actionQuit, &QAction::triggered, [=]() {
		g_pDirectorsCutApp->quit();
	});
	menuFile->addAction(actionQuit);
	menubar->addAction(menuFile->menuAction());

	QMenu* menuEdit = new QMenu("Edit", menubar);
	menuEdit->setDisabled(true);
	menubar->addAction(menuEdit->menuAction());
	QMenu* menuWindows = new QMenu("Windows", menubar);
	menuWindows->setDisabled(true);
	menubar->addAction(menuWindows->menuAction());
	QMenu* menuView = new QMenu("View", menubar);
	menuView->setDisabled(true);
	menubar->addAction(menuView->menuAction());
	QMenu* menuScripts = new QMenu("Scripts", menubar);
	menuScripts->setDisabled(true);
	menubar->addAction(menuScripts->menuAction());

	QMenu* menuHelp = new QMenu("Help", menubar);
	menubar->addAction(menuHelp->menuAction());
	QAction* actionAboutDirectorsCut = new QAction("About Director's Cut [Pre-Alpha]", menuHelp);
	connect(actionAboutDirectorsCut, &QAction::triggered, [=]() {
		CAboutDialog* about = new CAboutDialog(this);
		about->show();
	});
	menuHelp->addAction(actionAboutDirectorsCut);
	QAction* actionAboutQt = new QAction("About Qt", menuHelp);
	connect(actionAboutQt, &QAction::triggered, [=]() {
		QMessageBox::aboutQt(this);
	});
	menuHelp->addAction(actionAboutQt);
	
	// Status bar
	QStatusBar* statusbar = new QStatusBar(this);
	QLabel *statusLabel = new QLabel("[ Mem: 0000.00 MB | Game:  0000.0 | fps: 000.0/ 0.000 | Sample:  0000 of 0000 ]");
	statusbar->addPermanentWidget(statusLabel);
	setStatusBar(statusbar);

	// Main widget
	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
}

void CMainWindow::init()
{
}

#include "ui.h.moc"
