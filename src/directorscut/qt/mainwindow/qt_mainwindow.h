#pragma once

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include "qt_mainwindow_menubar.h"
#include "DockManager.h"

using namespace ads;

class CQtMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CQtMainWindow(QWidget* pParent);
	void populateMenus();
protected:
	void closeEvent(QCloseEvent* event) override;
	
	CDockManager* m_pDockManager;
	//QWidget* m_pDockManager;
	CQtMainWindowMenuBar* m_pMenuBar;
	QStatusBar* m_pStatusBar;
	QLabel *m_pStatusLabel;
};
