#pragma once

// This is where Qt is initialized
#include <QString>
#include <QApplication>
#include "qt/mainwindow/qt_mainwindow.h"

class CDirectorsCutQt
{
public:
    CDirectorsCutQt();
    ~CDirectorsCutQt();

    CQtMainWindow* GetMainWindow();
    void SetMainWindowVisible(bool visible);
    bool IsMainWindowVisible();
    bool CanQuit();

protected:
    QApplication* m_pApplication = nullptr;
    CQtMainWindow* m_pMainWindow = nullptr;
};
