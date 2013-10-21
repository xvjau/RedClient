#include <QApplication>

#include "redminemanager.h"

#include "mainwindow.h"

#include <QSystemTrayIcon>
#include <QMessageBox>

#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <QDebug>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
      
    app.setOrganizationName("B1tF0rge");
    app.setOrganizationDomain("bitforge.com.br");
    app.setApplicationName("RedClient");
    app.setApplicationDisplayName("Red Client");
      
    try
    {
        RedMineManager redmineManager(QUrl("https://projects.bitforge.com.br"));
        
        QQmlEngine engine;
        QObject::connect(&engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
        
        engine.rootContext()->setContextProperty("redmineManager", &redmineManager);
        
        
        MainWindow mw(&redmineManager);
        QSystemTrayIcon systemTrayIcon(QIcon("qrc://icons/icon.png"));
        
        if (QSystemTrayIcon::isSystemTrayAvailable())
            systemTrayIcon.show();
        else
            mw.show();
        
        return app.exec();
    }
    catch(const QString &e)
    {
        qDebug() << "QString error: " << e;
        return 1;
    }
    catch(const std::exception &e)
    {
        qDebug() << "Unknown error: " << e.what();
        return 1;
    }
    catch(int e)
    {
        return e;
    }
}
