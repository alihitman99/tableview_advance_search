#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>

#include "myproxymodel.h"

class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *qmlItem READ qmlItem WRITE setQmlItem NOTIFY qmlItemChanged FINAL)

public:
    explicit Manager(QQmlEngine *engine);

    QQuickItem *qmlItem() const;
    void setQmlItem(QQuickItem *newQmlItem);

    MyProxyModel *proxyModel() const;
    void setProxyModel(MyProxyModel *newProxyModel);

signals:
    void qmlItemChanged();

private:
    void createQml();

private:
    MyProxyModel *m_proxyModel = nullptr;
    QQuickItem *m_qmlItem = nullptr;
    QQmlEngine *m_engine = nullptr;
};

#endif // MANAGER_H
