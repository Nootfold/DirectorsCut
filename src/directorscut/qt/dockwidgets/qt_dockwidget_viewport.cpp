#include "qt_dockwidget_viewport.h"

CQtDockWidget_Viewport::CQtDockWidget_Viewport(int iviewportIndex, QWidget *parent) : CQtDockWidget(QString("Viewport"), parent)
{
    SetViewportIndex(iviewportIndex);
}

int CQtDockWidget_Viewport::GetViewportIndex()
{
    return m_iViewportIndex;
}

void CQtDockWidget_Viewport::SetViewportIndex(int iviewportIndex)
{
    m_iViewportIndex = iviewportIndex;
}

QString CQtDockWidget_Viewport::GetTitle()
{
    // "Primary Viewport", "Secondary Viewport", "Viewport 3", "Viewport 4", etc.
    if (m_iViewportIndex == 0)
    {
        return "Primary Viewport";
    }
    else if (m_iViewportIndex == 1)
    {
        return "Secondary Viewport";
    }
    else
    {
        return QString("Viewport %1").arg(m_iViewportIndex + 1);
    }
}

#include "qt_dockwidget_viewport.h.moc"
