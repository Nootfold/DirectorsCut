#include <QVBoxLayout>

#include "qt_dockwidget_viewport.h"
#include "tier3/tier3.h"

CQtDockWidget_Viewport::CQtDockWidget_Viewport(int iviewportIndex, QWidget *parent) : CQtDockWidget(QString("Viewport"), parent)
{
    // Create viewport and container
    m_pViewport = new CQtViewport(nullptr, iviewportIndex);
    m_pViewportContainer = QWidget::createWindowContainer(m_pViewport, this);
    // placeholders
    m_pViewportContainer->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    m_pViewportContainer->setMinimumSize(640, 480);
    m_pViewportContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pViewportContainer->setFocus();
    // simple layout (no margin)
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_pViewportContainer);
    setLayout(layout);
}

CQtDockWidget_Viewport::~CQtDockWidget_Viewport()
{
    // Destroy viewport and container
    delete m_pViewport;
    delete m_pViewportContainer;
}

QString CQtDockWidget_Viewport::GetTitle()
{
    // "Primary Viewport", "Secondary Viewport", "Viewport 3", "Viewport 4", etc.
    int iViewportIndex = m_pViewport->GetViewportIndex();
    if (iViewportIndex == 0)
    {
        return "Primary Viewport";
    }
    else if (iViewportIndex == 1)
    {
        return "Secondary Viewport";
    }
    else
    {
        return QString("Viewport %1").arg(iViewportIndex + 1);
    }
}

#include "qt_dockwidget_viewport.h.moc"
