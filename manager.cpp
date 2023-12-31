#include <QQmlComponent>

#include "manager.h"
#include "myproxymodel.h"

Manager::Manager(QQmlEngine *engine)
{
    m_proxyModel = new MyProxyModel;
    m_engine = engine;
    createQml();
}

void Manager::createQml()
{
    QQmlComponent *comp = new QQmlComponent(m_engine);

    connect(comp, &QQmlComponent::statusChanged, [&] {
        if (comp->status() == QQmlComponent::Status::Error) {
            qDebug() << comp->errorString();
        }

        m_qmlItem = qobject_cast<QQuickItem *>(comp->create());
        m_qmlItem->setProperty("tableModel", QVariant::fromValue(m_proxyModel));
    });

    comp->loadUrl(QUrl("qrc:/MyTableView.qml"));
}

MyProxyModel *Manager::proxyModel() const
{
    return m_proxyModel;
}

void Manager::setProxyModel(MyProxyModel *newProxyModel)
{
    m_proxyModel = newProxyModel;
}

QQuickItem *Manager::qmlItem() const
{
    return m_qmlItem;
}

void Manager::setQmlItem(QQuickItem *newQmlItem)
{
    if (m_qmlItem == newQmlItem)
        return;
    m_qmlItem = newQmlItem;
    emit qmlItemChanged();
}
