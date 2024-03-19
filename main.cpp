#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "publisher_thread.h"
#include <QDebug>

int main(int argc, char** argv)
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    PublisherThread publisher_thread;
    publisher_thread.init();
    engine.rootContext()->setContextProperty("PublisherThread", &publisher_thread);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}



