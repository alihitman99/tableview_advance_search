#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "list.h"
//#include "myproxymodel.h"
//#include "mytableview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

    ListManager *manager = new ListManager(engine);

    //manager->append(data);
    //we use myProxyModel and function of tableModel call in proxyModel with dynamic_cast
    //    engine.rootContext()->setContextProperty("tableModel",&table);
    engine->rootContext()->setContextProperty("managerInstance", manager);

    const QUrl url(u"qrc:/tableViewHoosham/Main.qml"_qs);
    QObject::connect(

        engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine->load(url);

    return app.exec();
}
