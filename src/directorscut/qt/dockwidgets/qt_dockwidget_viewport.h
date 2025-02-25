#pragma once

#include <QWidget>
#include "qt_viewport.h"
#include "qt_dockwidget.h"

class CQtDockWidget_Viewport : public CQtDockWidget
{
    Q_OBJECT
public:
    CQtDockWidget_Viewport(int iviewportIndex = 0, QWidget *parent = nullptr);
    virtual ~CQtDockWidget_Viewport();
    virtual QString GetTitle() override;
protected:
    CQtViewport* m_pViewport;
    QWidget* m_pViewportContainer;
};
