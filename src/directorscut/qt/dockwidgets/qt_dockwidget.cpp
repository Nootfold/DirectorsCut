#include "qt_dockwidget.h"
#include "directorscut.h"

CQtDockWidget::CQtDockWidget(QString title, QWidget* parent) : QWidget(parent)
{
    m_strTitle = title;
}

QString CQtDockWidget::GetTitle()
{
    return m_strTitle;
}

#include "qt_dockwidget.h.moc"
