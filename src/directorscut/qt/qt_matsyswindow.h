#pragma once

#include <QWidget>
#include <QWindow>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class CQtMatSysWindow : public QWindow
{
	Q_OBJECT;
public:
	CQtMatSysWindow(QWindow* pParent = nullptr);
	~CQtMatSysWindow();
	virtual void paint();
protected:
	bool m_bRemoving = false;
};
