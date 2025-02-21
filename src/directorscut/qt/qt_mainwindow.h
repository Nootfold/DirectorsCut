#pragma once

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include "qt_mainwindow_menubar.h"

class CQtMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CQtMainWindow(QWidget* pParent);
protected:
	void closeEvent(QCloseEvent* event) override;
	
	CQtMainWindowMenuBar* m_pMenuBar;
	QStatusBar* m_pStatusBar;
	QLabel *m_pStatusLabel;
	QWidget* m_pMainWidget;
};
