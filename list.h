#ifndef ListManager_H
#define ListManager_H

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include <QRandomGenerator>
#include <QSortFilterProxyModel>

//#include "myproxymodel.h"
class ListModel;
class ListProxyModel;
class ListManager;

//--------------------------------ListManager-----------------------
class ListManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *qmlItem READ qmlItem WRITE setQmlItem NOTIFY qmlItemChanged FINAL)

public:
    explicit ListManager(QQmlEngine *engine);

    QQuickItem *qmlItem() const;
    void setQmlItem(QQuickItem *newQmlItem);
    ListProxyModel *proxyModel() const;
    void setProxyModel(ListProxyModel *newProxyModel);
    //QString changeModel;

signals:
    void qmlItemChanged();

private:
    void createQml();

private:
    QQuickItem *m_qmlItem = nullptr;
    QQmlEngine *m_engine = nullptr;
    ListProxyModel *m_proxyModel = nullptr;
    ListProxyModel *m_newProxyModel = nullptr;
};

//--------------------------------------ListProxyModel-------------------------------------
class ListProxyModel : public QSortFilterProxyModel
{
    struct FilterTag
    {
        QString name;
        QString value;
    };

    struct FilterTag1
    {
        QString name;
        QString value;
    };
    struct FilterTag2
    {
        QString name;
        int valueFrom;
        int valueTo;
    };
    struct FilterTag3
    {
        QString name;
        int value;
        QString mark;
    };

    Q_OBJECT
    //Q_PROPERTY(QStringList comboItem READ comboItem WRITE setComboItem NOTIFY comboItemChanged FINAL)
    //Q_PROPERTY(QStringList comboItemList READ comboItemList WRITE setComboItemList NOTIFY comboItemListChanged FINAL)
public:
    explicit ListProxyModel(QObject *parent = nullptr);
    Q_INVOKABLE void sortTable(int column);
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    Q_INVOKABLE void nodeTypeFilter(QString type);
    Q_INVOKABLE void filterString(QString search, QString value);
    Q_INVOKABLE void filterStringColumn(QString tabName);
    Q_INVOKABLE QList<QString> getDataComboBox();
    Q_INVOKABLE QList<QString> getDataComboBoxInt();
    Q_INVOKABLE QList<QString> getColorFilter();
    Q_INVOKABLE void addTagColor(QString name, QString value);
    Q_INVOKABLE void addTag1(QString name, QString value);
    Q_INVOKABLE void addTag2(QString name, int value1, int value2);
    Q_INVOKABLE void addTag3(QString name, int value, QString mark);
    Q_INVOKABLE void removeTag(QString filterSearch, QString name, QString value);

    //QStringList comboItem() const;
    //void setComboItem(const QStringList &newComboItem);

    //QStringList comboItemList() const;
    //void setComboItemList(const QStringList &newComboItemList);

    Q_INVOKABLE QList<QString> getTabBarName();
    Q_INVOKABLE QStringList filterCombo(QString text, QString nameFilter);

    // dynamic_cast to ListModel
    Q_INVOKABLE void selectionRow(int Row, int Column);
    Q_INVOKABLE QItemSelectionModel *selectModel();
    Q_INVOKABLE void attacker(QString name);
    Q_INVOKABLE void setChangeModel(QString checkModel);
    Q_INVOKABLE QList<QString> getFilterData();

signals:
    //void comboItemChanged();

    //void comboItemListChanged();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    //QString m_filterColor;
    QString m_filterType;
    QString m_filterName;
    QString m_filterColumn;
    //int m_filterFrom;
    //int m_filterTo;
    //QString m_condition;
    QString m_searchTextCombo;

    QString m_search = ""; //filter check
    bool Asc = true;       //ascending or descending sort
    ListModel *listModel = nullptr;

    QVector<QString> columnName;
    QVector<QString> columnNameInt;
    QVector<QString> colorList;
    QVector<QString> tabList;
    QVector<QString> FilterDataList;

    QVector<QString> comboSearch;
    //QStringList m_comboItem;
    //QStringList m_comboItemList;

    QList<FilterTag> TagColor;
    QList<FilterTag1> TagFilter1;
    QList<FilterTag2> TagFilter2;
    QList<FilterTag3> TagFilter3;

    QStringList attakerList;

    enum Ecolumn {
        EColor = 0,
        EIcon,
        EName,
        ETn,
        ECallsing,
        EIFFcode,
        EIdentification,
        EType,
        EMaster,
        ELatitude,
        ELongitude,
        EAltitude,
        EPos,
        EHeading,
        ESpeed,
        EBattle,
        ETarget,
        EMore
    };
};
//-----------------------------------------ListModel------------------------------------
class ListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void selectionRow(int rowCount, int idxRow);
    Q_INVOKABLE QItemSelectionModel *selectModel();

    struct NodeFieldData
    {
        QString name;
        QVariant value;
        QString category;
    };

    struct NodeData
    {
        QVector<NodeFieldData> FieldData;
    };

    QVector<NodeData> Data;
    QVector<NodeData> *DataAttacker = new QVector<NodeData>;
    //QVector<NodeData> *DataAttack = new QVector<NodeData>;

    Q_INVOKABLE void attacker(QString name);
    Q_INVOKABLE void setChangeModel(QString checkModel);

private:
    QItemSelectionModel *selectionModel;
    QString modelType;
};

#endif // ListManager_H
