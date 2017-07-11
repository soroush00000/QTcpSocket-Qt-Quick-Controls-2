#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QIcon>
#include <QtCore>
#include <iostream>
#include <QTextStream>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    Client client;
    client.connectToHost("127.0.0.1");
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->setFlags( /*Qt::Dialog |*/ Qt::CustomizeWindowHint | Qt::WindowTitleHint );
    QObject::connect(window,SIGNAL(sendTextToC(QString)),&client,SLOT(getText(QString)));

    return app.exec();
}


