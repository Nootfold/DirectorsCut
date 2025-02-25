#pragma once

#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include "qt_aboutdialog.h"
#include "DockWidget.h"
#include "DockAreaWidget.h"

using namespace ads;

class CQtMainWindowMenuBar : public QMenuBar
{
	Q_OBJECT
public:
	CQtMainWindowMenuBar(QWidget* pParent);
	void PopulateMenus();
private slots:
	void AddWindowActions(QList<CDockWidget*> dockWidgets, QList<QAction*> actionList);
	// Menu dynamic population
	void onMenuFileAboutToShow();
	void onMenuEditAboutToShow();
	void onMenuWindowsAboutToShow();
	void onMenuViewAboutToShow();
	void onMenuScriptsAboutToShow();
	void onMenuHelpAboutToShow();
	// Actions
	void onActionShowFullscreenTriggered(bool checked=false);
	void onActionQuitTriggered(bool checked=false);
	void onActionParticleEditorToolTriggered(bool checked=false);
	void onActionEnterGameModeTriggered(bool checked=false);
	void onActionAutoHideEngineWindowTriggered(bool checked=false);
	void onActionAboutDirectorsCutTriggered(bool checked=false);
protected:
	QMenu* menuFile;
	QMenu* menuEdit;
	QMenu* menuWindows;
	QMenu* menuView;
	QMenu* menuScripts;
	QMenu* menuHelp;
	int m_iParticleMenuIndex = -1;
	bool m_bAutoHideEngineWindow = false;
};
