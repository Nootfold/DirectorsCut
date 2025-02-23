#include <QApplication>
#include <QtWidgets/QAction>
#include "tooldictionary.h"
#include "directorscut.h"
#include "qt_mainwindow_menubar.h"

CQtMainWindowMenuBar::CQtMainWindowMenuBar(QWidget* pParent) : QMenuBar(pParent)
{
	// Check if the Particle Editor tool is available
	for (int i = 0; i < enginetools->GetToolCount(); i++)
	{
		if(Q_strcmp(enginetools->GetToolName(i), "Particle Editor") == 0)
		{
			m_iParticleMenuIndex = i;
			break;
		}
	}

	// File menu
	menuFile = new QMenu("File", this);
	connect(menuFile, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuFileAboutToShow);
	addAction(menuFile->menuAction());

	// Edit menu
	menuEdit = new QMenu("Edit", this);
	connect(menuEdit, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuEditAboutToShow);
	menuEdit->setDisabled(true); // not yet implemented!
	addAction(menuEdit->menuAction());

	// Windows menu
	menuWindows = new QMenu("Windows", this);
	connect(menuWindows, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuWindowsAboutToShow);
	addAction(menuWindows->menuAction());

	// View menu
	menuView = new QMenu("View", this);
	connect(menuView, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuViewAboutToShow);
	addAction(menuView->menuAction());

	// Scripts menu
	menuScripts = new QMenu("Scripts", this);
	connect(menuScripts, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuScriptsAboutToShow);
	menuScripts->setDisabled(true); // not yet implemented!
	addAction(menuScripts->menuAction());

	// Help menu
	menuHelp = new QMenu("Help", this);
	connect(menuHelp, &QMenu::aboutToShow, this, &CQtMainWindowMenuBar::onMenuHelpAboutToShow);
	addAction(menuHelp->menuAction());
}

void CQtMainWindowMenuBar::populateMenus()
{
	// Initialize default menu items (ensures shortcuts are available)
	onMenuFileAboutToShow();
	onMenuEditAboutToShow();
	onMenuWindowsAboutToShow();
	onMenuViewAboutToShow();
	onMenuScriptsAboutToShow();
	onMenuHelpAboutToShow();
}

void CQtMainWindowMenuBar::onMenuFileAboutToShow()
{
	menuFile->clear();

	QAction* actionNew = new QAction("New", this);
	actionNew->setShortcut(QKeySequence::fromString("Ctrl+N"));
	actionNew->setDisabled(true);
	menuFile->addAction(actionNew);

	QAction* actionOpen = new QAction("Open...", this);
	actionOpen->setShortcut(QKeySequence::fromString("Ctrl+O"));
	actionOpen->setDisabled(true);
	menuFile->addAction(actionOpen);

	QAction* actionSave = new QAction("Save", this);
	actionSave->setShortcut(QKeySequence::fromString("Ctrl+S"));
	actionSave->setDisabled(true);
	menuFile->addAction(actionSave);

	QAction* actionSave_As = new QAction("Save As...", this);
	actionSave_As->setDisabled(true);
	menuFile->addAction(actionSave_As);

	QAction* actionClose = new QAction("Close", this);
	actionClose->setDisabled(true);
	menuFile->addAction(actionClose);

	menuFile->addSeparator();

	QMenu* menuPerforce = new QMenu("Perforce", menuFile);
	menuPerforce->setDisabled(true);
	menuFile->addMenu(menuPerforce);

		QAction* actionAdd = new QAction("Add", this);
		actionAdd->setDisabled(true);
		menuPerforce->addAction(actionAdd);

		QAction* actionCheckout = new QAction("Checkout", this);
		actionCheckout->setDisabled(true);
		menuPerforce->addAction(actionCheckout);

		QAction* actionRevert = new QAction("Revert", this);
		actionRevert->setDisabled(true);
		menuPerforce->addAction(actionRevert);

		QAction* actionSubmit = new QAction("Submit", this);
		actionSubmit->setDisabled(true);
		menuPerforce->addAction(actionSubmit);

		menuPerforce->addSeparator();

		QAction* actionList_Open_Files = new QAction("List Open Files", this);
		actionList_Open_Files->setDisabled(true);
		menuPerforce->addAction(actionList_Open_Files);

		menuPerforce->addSeparator();

		QAction* actionView_In_P4Win = new QAction("View in P4Win", this);
		actionView_In_P4Win->setDisabled(true);
		menuPerforce->addAction(actionView_In_P4Win);

		QAction* actionView_In_P4V = new QAction("View in P4V", this);
		actionView_In_P4V->setDisabled(true);
		menuPerforce->addAction(actionView_In_P4V);

		menuPerforce->addSeparator();

		QAction* actionCheck_For_Perforce = new QAction("Check for Perforce", this);
		actionCheck_For_Perforce->setDisabled(true);
		menuPerforce->addAction(actionCheck_For_Perforce);

	QMenu* menuRecent = new QMenu("Recent", menuFile);
	menuRecent->setDisabled(true);
	menuFile->addMenu(menuRecent);

		menuRecent->addSeparator();

		QAction* actionClear_Recent = new QAction("Clear Recent", this);
		actionClear_Recent->setDisabled(true);
		menuRecent->addAction(actionClear_Recent);

	menuFile->addSeparator();

	QAction* actionLoad_Map = new QAction("Load Map", this);
	actionLoad_Map->setShortcut(QKeySequence::fromString("Ctrl+L"));
	actionLoad_Map->setDisabled(true);
	menuFile->addAction(actionLoad_Map);

	menuFile->addSeparator();

	QMenu* menuImport = new QMenu("Import", menuFile);
	menuImport->setDisabled(true);
	menuFile->addMenu(menuImport);

		QAction* actionRender_Settings = new QAction("Render Settings", this);
		actionRender_Settings->setDisabled(true);
		menuImport->addAction(actionRender_Settings);

		QAction* actionMovie_Settings = new QAction("Movie Settings", this);
		actionMovie_Settings->setDisabled(true);
		menuImport->addAction(actionMovie_Settings);

	QMenu* menuExport = new QMenu("Export", menuFile);
	menuExport->setDisabled(true);
	menuFile->addMenu(menuExport);

		QAction* actionMovie = new QAction("Movie", this);
		actionMovie->setDisabled(true);
		menuExport->addAction(actionMovie);

		QAction* actionPoster = new QAction("Poster", this);
		actionPoster->setDisabled(true);
		menuExport->addAction(actionPoster);

		QAction* actionImage = new QAction("Image", this);
		actionImage->setDisabled(true);
		menuExport->addAction(actionImage);

		menuExport->addSeparator();

		QAction* actionImage_To_Clipboard = new QAction("Image to Clipboard", this);
		actionImage_To_Clipboard->setDisabled(true);
		menuExport->addAction(actionImage_To_Clipboard);

		menuExport->addSeparator();

		QAction* actionRender_Settings2 = new QAction("Render Settings", this);
		actionRender_Settings2->setDisabled(true);
		menuExport->addAction(actionRender_Settings2);

		QAction* actionMovie_Settings2 = new QAction("Movie Settings", this);
		actionMovie_Settings2->setDisabled(true);
		menuExport->addAction(actionMovie_Settings2);

	QMenu* menuCommunity = new QMenu("Community", menuFile);
	menuCommunity->setDisabled(true);
	menuFile->addMenu(menuCommunity);

		QAction* actionPublish_Video_To_YouTube_And_Steam = new QAction("Publish Video to YouTube and Steam", this);
		actionPublish_Video_To_YouTube_And_Steam->setDisabled(true);
		menuCommunity->addAction(actionPublish_Video_To_YouTube_And_Steam);

		QAction* actionPublish_Image_To_Steam = new QAction("Publish Image to Steam", this);
		actionPublish_Image_To_Steam->setDisabled(true);
		menuCommunity->addAction(actionPublish_Image_To_Steam);

		QMenu* menuPublish_To_Steam_Workshop = new QMenu("Publish to Steam Workshop", menuCommunity);
		menuPublish_To_Steam_Workshop->setDisabled(true);
		menuCommunity->addMenu(menuPublish_To_Steam_Workshop);

			QAction* actionSounds = new QAction("Sounds", this);
			actionSounds->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionSounds);

			QAction* actionModels = new QAction("Models", this);
			actionModels->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionModels);

			QAction* actionMaps = new QAction("Maps", this);
			actionMaps->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionMaps);

			QAction* actionParticles = new QAction("Particles", this);
			actionParticles->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionParticles);

			QAction* actionScripts = new QAction("Scripts", this);
			actionScripts->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionScripts);

			QAction* actionMaterials = new QAction("Materials", this);
			actionMaterials->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionMaterials);

			QAction* actionTextures = new QAction("Textures", this);
			actionTextures->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionTextures);

			QAction* actionSessions = new QAction("Sessions", this);
			actionSessions->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionSessions);

			QAction* actionShots = new QAction("Shots", this);
			actionShots->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionShots);

			QAction* actionAnimations = new QAction("Animations", this);
			actionAnimations->setDisabled(true);
			menuPublish_To_Steam_Workshop->addAction(actionAnimations);

		QMenu* menuUpdate_Published_Item = new QMenu("Update Published Item", menuCommunity);
		menuUpdate_Published_Item->setDisabled(true);
		menuCommunity->addMenu(menuUpdate_Published_Item);

			menuUpdate_Published_Item->addSeparator();

			QAction* actionRefresh_Published_Item_List = new QAction("Refresh Published Item List", this);
			actionRefresh_Published_Item_List->setDisabled(true);
			menuUpdate_Published_Item->addAction(actionRefresh_Published_Item_List);

		QMenu* menuBrowse_To_Your_Published_Items = new QMenu("Browse To Your Published Items", menuCommunity);
		menuBrowse_To_Your_Published_Items->setDisabled(true);
		menuCommunity->addMenu(menuBrowse_To_Your_Published_Items);

			QAction* actionVideos = new QAction("Videos", this);
			actionVideos->setDisabled(true);
			menuBrowse_To_Your_Published_Items->addAction(actionVideos);

			QAction* actionImages = new QAction("Images", this);
			actionImages->setDisabled(true);
			menuBrowse_To_Your_Published_Items->addAction(actionImages);

			QAction* actionWorkshop = new QAction("Workshop", this);
			actionWorkshop->setDisabled(true);
			menuBrowse_To_Your_Published_Items->addAction(actionWorkshop);

		QMenu* menuBrowse_To_All_Published_Items = new QMenu("Browse To All Published Items", menuCommunity);
		menuBrowse_To_All_Published_Items->setDisabled(true);
		menuCommunity->addMenu(menuBrowse_To_All_Published_Items);

			QAction* actionVideos2 = new QAction("Videos", this);
			actionVideos2->setDisabled(true);
			menuBrowse_To_All_Published_Items->addAction(actionVideos2);

			QAction* actionImages2 = new QAction("Images", this);
			actionImages2->setDisabled(true);
			menuBrowse_To_All_Published_Items->addAction(actionImages2);

			QAction* actionWorkshop2 = new QAction("Workshop", this);
			actionWorkshop2->setDisabled(true);
			menuBrowse_To_All_Published_Items->addAction(actionWorkshop2);

		menuCommunity->addSeparator();

		QAction* actionShow_Used_Workshop_Items = new QAction("Show Used Workshop Items", this);
		actionShow_Used_Workshop_Items->setDisabled(true);
		menuCommunity->addAction(actionShow_Used_Workshop_Items);

	QMenu* menuDownloadable_Content = new QMenu("Downloadable Content", menuFile);
	menuDownloadable_Content->setDisabled(true);
	menuFile->addMenu(menuDownloadable_Content);

		QAction* actionInstall_Day_Of_Defeat_Content_Pack = new QAction("Install Day Of Defeat Content Pack", this);
		actionInstall_Day_Of_Defeat_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Day_Of_Defeat_Content_Pack);

		QAction* actionInstall_Portal_Content_Pack = new QAction("Install Portal Content Pack", this);
		actionInstall_Portal_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Portal_Content_Pack);

		QAction* actionInstall_Blade_Symphony_Content_Pack = new QAction("Install Blade Symphony Content Pack", this);
		actionInstall_Blade_Symphony_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Blade_Symphony_Content_Pack);

		QAction* actionInstall_Black_Mesa_Content_Pack = new QAction("Install Black Mesa Content Pack", this);
		actionInstall_Black_Mesa_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Black_Mesa_Content_Pack);

		QAction* actionInstall_Left_4_Dead_Content_Pack = new QAction("Install Left 4 Dead Content Pack", this);
		actionInstall_Left_4_Dead_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Left_4_Dead_Content_Pack);

		QAction* actionInstall_Dino_D_Day_Content_Pack = new QAction("Install Dino D-Day Content Pack", this);
		actionInstall_Dino_D_Day_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_Dino_D_Day_Content_Pack);

		QAction* actionInstall_The_Stanley_Parable_Content_Pack = new QAction("Install The Stanley Parable Content Pack", this);
		actionInstall_The_Stanley_Parable_Content_Pack->setDisabled(true);
		menuDownloadable_Content->addAction(actionInstall_The_Stanley_Parable_Content_Pack);
	
	menuFile->addSeparator();

	QAction* actionQuit = new QAction("Quit", this);
	connect(actionQuit, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionQuitTriggered);
	menuFile->addAction(actionQuit);
}

void CQtMainWindowMenuBar::onMenuEditAboutToShow()
{
	menuEdit->clear();

	QAction* actionUndo = new QAction("Undo", this);
	actionUndo->setShortcut(QKeySequence::fromString("Ctrl+Z"));
	actionUndo->setDisabled(true);
	menuEdit->addAction(actionUndo);
	
	QAction* actionRedo = new QAction("Redo", this);
	actionRedo->setShortcut(QKeySequence::fromString("Ctrl+Shift+Z"));
	actionRedo->setDisabled(true);
	menuEdit->addAction(actionRedo);

	menuEdit->addSeparator();

	QAction* actionCut = new QAction("Cut", this);
	actionCut->setShortcut(QKeySequence::fromString("Ctrl+X"));
	actionCut->setDisabled(true);
	menuEdit->addAction(actionCut);

	QAction* actionCopy = new QAction("Copy", this);
	actionCopy->setShortcut(QKeySequence::fromString("Ctrl+C"));
	actionCopy->setDisabled(true);
	menuEdit->addAction(actionCopy);

	QAction* actionPaste = new QAction("Paste", this);
	actionPaste->setShortcut(QKeySequence::fromString("Ctrl+V"));
	actionPaste->setDisabled(true);
	menuEdit->addAction(actionPaste);

	QAction* actionDelete = new QAction("Delete", this);
	actionDelete->setShortcut(QKeySequence::fromString("Del"));
	actionDelete->setDisabled(true);
	menuEdit->addAction(actionDelete);
}

void CQtMainWindowMenuBar::onMenuWindowsAboutToShow()
{
	menuWindows->clear();

	QAction* actionElement_Viewer = new QAction("Element Viewer", this);
	actionElement_Viewer->setShortcut(QKeySequence::fromString("F9"));
	actionElement_Viewer->setDisabled(true);
	menuWindows->addAction(actionElement_Viewer);

	menuWindows->addSeparator();

	QAction* actionClip_Editor = new QAction("Clip Editor", this);
	actionClip_Editor->setShortcut(QKeySequence::fromString("F2"));
	actionClip_Editor->setDisabled(true);
	menuWindows->addAction(actionClip_Editor);

	QAction* actionMotion_Editor = new QAction("Motion Editor", this);
	actionMotion_Editor->setShortcut(QKeySequence::fromString("F3"));
	actionMotion_Editor->setDisabled(true);
	menuWindows->addAction(actionMotion_Editor);

	QAction* actionGraph_Editor = new QAction("Graph Editor", this);
	actionGraph_Editor->setShortcut(QKeySequence::fromString("F4"));
	actionGraph_Editor->setDisabled(true);
	menuWindows->addAction(actionGraph_Editor);

	QAction* actionAnimation_Set_Editor = new QAction("Animation Set Editor", this);
	actionAnimation_Set_Editor->setDisabled(true);
	menuWindows->addAction(actionAnimation_Set_Editor);

	menuWindows->addSeparator();

	QAction* actionPrimary_Viewport = new QAction("Primary Viewport", this);
	actionPrimary_Viewport->setDisabled(true);
	menuWindows->addAction(actionPrimary_Viewport);

	QAction* actionSecondary_Viewport = new QAction("Secondary Viewport", this);
	actionSecondary_Viewport->setDisabled(true);
	menuWindows->addAction(actionSecondary_Viewport);

	menuWindows->addSeparator();

	QAction* actionConsole = new QAction("Console", this);
	actionConsole->setDisabled(true);
	menuWindows->addAction(actionConsole);

	QAction* actionScript_Editor = new QAction("Script Editor", this);
	actionScript_Editor->setDisabled(true);
	menuWindows->addAction(actionScript_Editor);

	QAction* actionHistory = new QAction("History", this);
	actionHistory->setDisabled(true);
	menuWindows->addAction(actionHistory);

	menuWindows->addSeparator();

	QAction* actionParticle_Editor_Tool = new QAction("Particle Editor Tool", this);
	connect(actionParticle_Editor_Tool, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionParticleEditorToolTriggered);
	actionParticle_Editor_Tool->setDisabled(m_iParticleMenuIndex == -1);
	menuWindows->addAction(actionParticle_Editor_Tool);

	QAction* actionEnter_Game_Mode = new QAction("Enter Game Mode", this);
	actionEnter_Game_Mode->setShortcut(QKeySequence::fromString("F11"));
	connect(actionEnter_Game_Mode, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionEnterGameModeTriggered);
	menuWindows->addAction(actionEnter_Game_Mode);

	QMenu* menuEngine_Window = new QMenu("Engine Window", menuWindows);
	menuWindows->addAction(menuEngine_Window->menuAction());

		QAction* actionAuto_Hide_Engine_Window = new QAction("Auto Hide Engine Window", this);
		actionAuto_Hide_Engine_Window->setCheckable(true);
		actionAuto_Hide_Engine_Window->setChecked(g_pDirectorsCutTool->GetShouldHideEngineWindow());
		connect(actionAuto_Hide_Engine_Window, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionAutoHideEngineWindowTriggered);
		menuEngine_Window->addAction(actionAuto_Hide_Engine_Window);

	menuWindows->addSeparator();

	QAction* actionShow_All_Windows = new QAction("Show All Windows", this);
	actionShow_All_Windows->setDisabled(true);
	menuWindows->addAction(actionShow_All_Windows);

	menuWindows->addSeparator();

	QMenu* menuLayout = new QMenu("Layout", menuWindows);
	menuLayout->setDisabled(true);
	menuWindows->addMenu(menuLayout);

		QAction* actionReturn_To_Default_Layout = new QAction("Return to Default Layout", this);
		actionReturn_To_Default_Layout->setDisabled(true);
		menuLayout->addAction(actionReturn_To_Default_Layout);

		QAction* actionSave_Layout = new QAction("Save Layout", this);
		actionSave_Layout->setDisabled(true);
		menuLayout->addAction(actionSave_Layout);

		menuLayout->addSeparator();

		QAction* actionDefault = new QAction("Default", this);
		actionDefault->setCheckable(true);
		actionDefault->setChecked(true);
		actionDefault->setDisabled(true);
		menuLayout->addAction(actionDefault);

		QAction* actionClip_Editing = new QAction("Clip Editing", this);
		actionClip_Editing->setCheckable(true);
		actionClip_Editing->setDisabled(true);
		menuLayout->addAction(actionClip_Editing);

		QAction* actionMotion_Editing = new QAction("Motion Editing", this);
		actionMotion_Editing->setCheckable(true);
		actionMotion_Editing->setDisabled(true);
		menuLayout->addAction(actionMotion_Editing);

		QAction* actionKeyframing = new QAction("Keyframing", this);
		actionKeyframing->setCheckable(true);
		actionKeyframing->setDisabled(true);
		menuLayout->addAction(actionKeyframing);

		QAction* actionSound_Editing = new QAction("Sound Editing", this);
		actionSound_Editing->setCheckable(true);
		actionSound_Editing->setDisabled(true);
		menuLayout->addAction(actionSound_Editing);

		QAction* actionCustom_Layout_5 = new QAction("Custom Layout 5", this);
		actionCustom_Layout_5->setCheckable(true);
		actionCustom_Layout_5->setDisabled(true);
		menuLayout->addAction(actionCustom_Layout_5);

		QAction* actionCustom_Layout_6 = new QAction("Custom Layout 6", this);
		actionCustom_Layout_6->setCheckable(true);
		actionCustom_Layout_6->setDisabled(true);
		menuLayout->addAction(actionCustom_Layout_6);

		QAction* actionCustom_Layout_7 = new QAction("Custom Layout 7", this);
		actionCustom_Layout_7->setCheckable(true);
		actionCustom_Layout_7->setDisabled(true);		
		menuLayout->addAction(actionCustom_Layout_7);

		QAction* actionCustom_Layout_8 = new QAction("Custom Layout 8", this);
		actionCustom_Layout_8->setCheckable(true);	
		actionCustom_Layout_8->setDisabled(true);
		menuLayout->addAction(actionCustom_Layout_8);

		QAction* actionCustom_Layout_9 = new QAction("Custom Layout 9", this);
		actionCustom_Layout_9->setCheckable(true);
		actionCustom_Layout_9->setDisabled(true);
		menuLayout->addAction(actionCustom_Layout_9);

		menuLayout->addSeparator();

		QAction* actionRename_Layout = new QAction("Rename Layout...", this);
		actionRename_Layout->setDisabled(true);
		menuLayout->addAction(actionRename_Layout);

		QAction* actionReset_Layouts = new QAction("Reset Layouts", this);
		actionReset_Layouts->setDisabled(true);
		menuLayout->addAction(actionReset_Layouts);

		menuLayout->addSeparator();

		QAction* actionImport_Layout = new QAction("Import Layout...", this);
		actionImport_Layout->setDisabled(true);
		menuLayout->addAction(actionImport_Layout);

		QAction* actionExport_Layout = new QAction("Export Layout...", this);
		actionExport_Layout->setDisabled(true);
		menuLayout->addAction(actionExport_Layout);
}

void CQtMainWindowMenuBar::onMenuViewAboutToShow()
{
	menuView->clear();

	QAction* actionShow_Fullscreen = new QAction("Show Fullscreen", this);
	// If the main window is in fullscreen mode, change the text to "Show Normal"
	if (g_pDirectorsCutTool->Qt()->GetMainWindow()->windowState() & Qt::WindowFullScreen)
	{
		actionShow_Fullscreen->setText("Show Normal");
	}
	actionShow_Fullscreen->setShortcut(QKeySequence::fromString("Ctrl+Shift+F"));
	connect(actionShow_Fullscreen, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionShowFullscreenTriggered);
	menuView->addAction(actionShow_Fullscreen);

	QAction* actionShow_Primary_Viewport_Controls = new QAction("Show Primary Viewport Controls", this);
	actionShow_Primary_Viewport_Controls->setShortcut(QKeySequence::fromString("Ctrl+Alt+E"));
	actionShow_Primary_Viewport_Controls->setCheckable(true);
	actionShow_Primary_Viewport_Controls->setChecked(true);
	actionShow_Primary_Viewport_Controls->setDisabled(true);
	menuView->addAction(actionShow_Primary_Viewport_Controls);

	QAction* actionShow_Secondary_Viewport_Controls = new QAction("Show Secondary Viewport Controls", this);
	actionShow_Secondary_Viewport_Controls->setCheckable(true);
	actionShow_Secondary_Viewport_Controls->setChecked(true);
	actionShow_Secondary_Viewport_Controls->setDisabled(true);
	menuView->addAction(actionShow_Secondary_Viewport_Controls);
}

void CQtMainWindowMenuBar::onMenuScriptsAboutToShow()
{
	menuScripts->clear();

	menuScripts->addSeparator();

	QAction* actionShow_In_Explorer = new QAction("Show in Explorer", this);
	actionShow_In_Explorer->setDisabled(true);
	menuScripts->addAction(actionShow_In_Explorer);
}

void CQtMainWindowMenuBar::onMenuHelpAboutToShow()
{
	menuHelp->clear();

	QAction* actionHelp = new QAction("Help...", this);
	actionHelp->setShortcut(QKeySequence::fromString("F1"));
	actionHelp->setDisabled(true);
	menuHelp->addAction(actionHelp);

	QAction* actionKeyboard_Shortcuts = new QAction("Keyboard Shortcuts", this);
	actionKeyboard_Shortcuts->setShortcut(QKeySequence::fromString("Ctrl+Alt+Shift+E"));
	actionKeyboard_Shortcuts->setDisabled(true);
	menuHelp->addAction(actionKeyboard_Shortcuts);

	menuHelp->addSeparator();

	QAction* actionScreencast = new QAction("Screencast", this);
	actionScreencast->setDisabled(true);
	menuHelp->addAction(actionScreencast);

	QAction* actionScreencast_Slides = new QAction("Screencast Slides", this);
	actionScreencast_Slides->setDisabled(true);
	menuHelp->addAction(actionScreencast_Slides);

	menuHelp->addSeparator();

	QAction* actionResetSettings = new QAction("Reset Settings", this);
	actionResetSettings->setDisabled(true);
	menuHelp->addAction(actionResetSettings);

	menuHelp->addSeparator();

	QAction* actionVisit_Forums = new QAction("Visit Forums", this);
	actionVisit_Forums->setDisabled(true);
	menuHelp->addAction(actionVisit_Forums);

	QAction* actionVisit_Steam_Community = new QAction("Visit Steam Community", this);
	actionVisit_Steam_Community->setDisabled(true);
	menuHelp->addAction(actionVisit_Steam_Community);

	QAction* actionContact_Us = new QAction("Contact Us", this);
	actionContact_Us->setDisabled(true);
	menuHelp->addAction(actionContact_Us);

	QAction* actionReport_Bug = new QAction("Report Bug", this);
	actionReport_Bug->setDisabled(true);
	menuHelp->addAction(actionReport_Bug);

	menuHelp->addSeparator();

	QAction* actionDirectors_Cut_Subscription_Terms = new QAction(DIRECTORSCUT_PRODUCTNAME " Subscription Terms", this);
	actionDirectors_Cut_Subscription_Terms->setDisabled(true);
	menuHelp->addAction(actionDirectors_Cut_Subscription_Terms);

	QAction* actionSteam_Subscriber_Agreement = new QAction("Steam Subscriber Agreement", this);
	actionSteam_Subscriber_Agreement->setDisabled(true);
	menuHelp->addAction(actionSteam_Subscriber_Agreement);

	menuHelp->addSeparator();

	QAction* actionAbout_Directors_Cut = new QAction("About " DIRECTORSCUT_PRODUCTNAME " [" DIRECTORSCUT_DEVELOPMENT_STAGE "]", this);
	connect(actionAbout_Directors_Cut, &QAction::triggered, this, &CQtMainWindowMenuBar::onActionAboutDirectorsCutTriggered);
	menuHelp->addAction(actionAbout_Directors_Cut);

	QAction* actionAbout_Qt = new QAction("About Qt", this);
	connect(actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);
	menuHelp->addAction(actionAbout_Qt);
}


void CQtMainWindowMenuBar::onActionShowFullscreenTriggered(bool checked)
{
    CQtMainWindow* mainWindow = g_pDirectorsCutTool->Qt()->GetMainWindow();
    mainWindow->setWindowState(mainWindow->windowState() ^ Qt::WindowFullScreen);
}

void CQtMainWindowMenuBar::onActionQuitTriggered(bool checked)
{
    g_pDirectorsCutTool->Qt()->GetMainWindow()->close();
}

void CQtMainWindowMenuBar::onActionParticleEditorToolTriggered(bool checked)
{
	// Check if the Particle Editor tool is available
	if(m_iParticleMenuIndex != -1)
	{
		enginetools->SwitchToTool(m_iParticleMenuIndex);
	}
}

void CQtMainWindowMenuBar::onActionEnterGameModeTriggered(bool checked)
{
	g_pDirectorsCutTool->ToggleTool();
}

void CQtMainWindowMenuBar::onActionAutoHideEngineWindowTriggered(bool checked)
{
    bool hide = !g_pDirectorsCutTool->GetShouldHideEngineWindow();
    g_pDirectorsCutTool->SetShouldHideEngineWindow(hide);
    g_pDirectorsCutTool->HideOrShowEngineWindow(hide);
}

void CQtMainWindowMenuBar::onActionAboutDirectorsCutTriggered(bool checked)
{
	// Open our custom about dialog
    CQtAboutDialog* dialog = new CQtAboutDialog(this);
    dialog->show();
    dialog->activateWindow();
}

#include "qt_mainwindow_menubar.h.moc"
