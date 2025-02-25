#pragma once

#include <QString>
#include "KeyValues.h"
#include "matsys_controls/matsyscontrols.h"
#include "vguimatsurface/IMatSystemSurface.h"
#include "materialsystem/MaterialSystemUtil.h"
#include "materialsystem/imaterial.h"
#include "qt/qt_matsyswindow.h"

class CQtViewport : public CQtMatSysWindow
{
    Q_OBJECT
public:
    CQtViewport(QWindow* pParent, int iviewportIndex = 0);
    ~CQtViewport();
    virtual void paint() override;

    int GetViewportIndex();
    void SetViewportIndex(int iviewportIndex);
protected:
    int m_iViewportIndex = 0;
};