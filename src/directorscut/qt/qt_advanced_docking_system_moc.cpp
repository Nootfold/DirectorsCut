// This file is used to implement the Qt MOC preprocessor for Qt Advanced Docking System classes.
// There is no way to automatically run MOC while using VPC project definitions.

// ADS resources aren't necessary becuase we use a custom style sheet
int __cdecl qInitResources_ads(void)
{
    return 0;
}

// Include generated MOC files (see qt_advanced_docking_system.vpc)
#include "ads_globals.h.moc"
#include "AutoHideDockContainer.h.moc"
#include "AutoHideSideBar.h.moc"
#include "AutoHideTab.h.moc"
#include "DockAreaTabBar.h.moc"
#include "DockAreaTitleBar.h.moc"
#include "DockAreaTitleBar_p.h.moc"
#include "DockAreaWidget.h.moc"
#include "DockComponentsFactory.h.moc"
#include "DockContainerWidget.h.moc"
#include "DockFocusController.h.moc"
#include "DockingStateReader.h.moc"
#include "DockManager.h.moc"
#include "DockOverlay.h.moc"
#include "DockSplitter.h.moc"
#include "DockWidget.h.moc"
#include "DockWidgetTab.h.moc"
#include "ElidingLabel.h.moc"
#include "FloatingDockContainer.h.moc"
#include "FloatingDragPreview.h.moc"
#include "IconProvider.h.moc"
#include "PushButton.h.moc"
#include "ResizeHandle.h.moc"
