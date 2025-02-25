#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "directorscut.h"

// This handles Qt outside of the main class
CDirectorsCutQt::CDirectorsCutQt()
{
	Msg("Initialising Qt5\n");

    // Initialize search path
    QString searchPath = "bin/directorscut";
    QDir::addSearchPath("tools", searchPath);

    // Initialize plugin (library) path
    QString libraryPath = "bin/directorscut/x64";
    QStringList paths;
    QString cwd = QDir::currentPath();
    paths.append(cwd + "/" + libraryPath);
    QCoreApplication::setLibraryPaths(paths);

    // Create application
    int argc = 0;
    m_pApplication = new QApplication(argc, nullptr);

    // Load stylesheet
    QFile file("tools:stylesheets/directorscut.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        m_pApplication->setStyleSheet(styleSheet);
    } else {
        // User-friendly error message
        QMessageBox::critical(nullptr, "Error", QString("Failed to load stylesheet. %1 will use the default Qt stylesheet.").arg(DIRECTORSCUT_PRODUCTNAME));
    }
    
	// we MUST close the app after the home window is gone,
	// since we are not using ::exec();
	QApplication::setQuitOnLastWindowClosed(true);

    // Create main window
    m_pMainWindow = new CQtMainWindow(nullptr);
}
 
CDirectorsCutQt::~CDirectorsCutQt()
{
    // Destroy members and shut down Qt
    if (m_pMainWindow)
    {
        m_pMainWindow->close();
        delete m_pMainWindow;
        m_pMainWindow = nullptr;
    }
    if (m_pApplication)
    {
        m_pApplication->quit();
        delete m_pApplication;
        m_pApplication = nullptr;
    }
}

CQtMainWindow* CDirectorsCutQt::GetMainWindow()
{
    return m_pMainWindow;
}

void CDirectorsCutQt::SetMainWindowVisible(bool visible)
{
    if (m_pMainWindow)
    {
        if (visible)
        {
            m_pMainWindow->show();
            m_pMainWindow->activateWindow();
        }
        else
        {
            m_pMainWindow->hide();
        }
    }
}

bool CDirectorsCutQt::IsMainWindowVisible()
{
    return m_pMainWindow && m_pMainWindow->isVisible();
}

bool CDirectorsCutQt::CanQuit()
{
    // Only allow the tool to quit if no modal dialogs are open
    return QApplication::activeModalWidget() == nullptr;
}
