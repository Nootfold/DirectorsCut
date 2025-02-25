#pragma once

// This is where Qt is initialized
#include <QString>
#include <QApplication>
#include "qt/mainwindow/qt_mainwindow.h"
#include "qt/qt_matsyswindow.h"

class CDirectorsCutQt
{
public:
    CDirectorsCutQt();
    ~CDirectorsCutQt();

    CQtMainWindow* GetMainWindow();
    void SetMainWindowVisible(bool visible);
    bool IsMainWindowVisible();
    bool CanQuit();
    void AddManagedView(CQtMatSysWindow* pView);
    void RemoveManagedView(CQtMatSysWindow* pView);
    void DrawManagedViews();
protected:
    QApplication* m_pApplication = nullptr;
    CQtMainWindow* m_pMainWindow = nullptr;
    CUtlVector<CQtMatSysWindow*> m_vecManagedViews;
};
