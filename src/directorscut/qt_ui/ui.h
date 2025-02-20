#pragma once
#include <QWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>
#include <QMainWindow>
#include <QtWidgets/QDoubleSpinBox>

class CMainWindow : public QMainWindow
{
	Q_OBJECT;
public:

	CMainWindow(QWidget* pParent);

	void init();
};
