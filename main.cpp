#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mytableview.h"
#include "myproxymodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MyTableView table;
    MyProxyModel proxyModel;
    proxyModel.setSourceModel(&table);

    QQmlApplicationEngine engine;
//    QVector<QObject*> colorList;
//    colorList.append(new Color("color", "red", &engine));

//we use myProxyModel and function of tableModel call in proxyModel with dynamic_cast
//    engine.rootContext()->setContextProperty("tableModel",&table);
    engine.rootContext()->setContextProperty("myProxyModel", &proxyModel);

    const QUrl url(u"qrc:/tableViewHoosham/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
