#pragma once

#include "utlvector.h"
#include "qt_dockwidget.h"

class CQtDockWidget_Viewport : public CQtDockWidget
{
    Q_OBJECT
public:
    CQtDockWidget_Viewport(int iviewportIndex = 0, QWidget *parent = nullptr);
    int GetViewportIndex();
    void SetViewportIndex(int iviewportIndex);
    virtual QString GetTitle() override;
protected:
    int m_iViewportIndex;
};
