#pragma once

#include <QWidget>
#include "DockManager.h"
using namespace ads;

class CQtDockWidget : public QWidget
{
    Q_OBJECT
public:
    CQtDockWidget(QString title = QString("Dock Widget"), QWidget* parent = nullptr);
    virtual QString GetTitle();
protected:
    QString m_strTitle;
};
