#include <QApplication>

#include "redminemanager.h"

#include "mainwindow.h"

#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <QDebug>

QQuickWindow* createAndShow(QQmlEngine &_engine, const QUrl &_url)
{
    QQmlComponent *component = new QQmlComponent(&_engine);
    component->loadUrl(_url);
    
    QObject *topLevel = component->create();
    if (component->isError())
    {
        qDebug() << "QML loading error:";
        for(auto error : component->errors())
        {
            qDebug() << error.url().toString() << ':' << error.line() << ':' << error.column() << " - " << error.description() << "\n";
        }
        qDebug() << "\n";
        
        throw 2;
    }
    else
    {
        QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
        
        window->show();
        return window;
    }
}

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
        
        //createAndShow(engine, QUrl("qrc:/qml/MainWindow.qml"));
        
        MainWindow mw(&redmineManager);
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
