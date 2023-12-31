#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>

#include "mytableview.h"

class MyProxyModel : public QSortFilterProxyModel
{
    struct FilterTag{
        QString name;
        QString value;
    };

    struct FilterTag1{
        QString name;
        QString value;
    };
    struct FilterTag2{
        QString name;
        int valueFrom;
        int valueTo;
    };
    struct FilterTag3{
        QString name;
        int value;
        QString mark;
    };

    Q_OBJECT
    //Q_PROPERTY(QStringList comboItem READ comboItem WRITE setComboItem NOTIFY comboItemChanged FINAL)
    //Q_PROPERTY(QStringList comboItemList READ comboItemList WRITE setComboItemList NOTIFY comboItemListChanged FINAL)
public:
    explicit MyProxyModel(QObject *parent = nullptr);
    Q_INVOKABLE void sortTable(int column);
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    Q_INVOKABLE void filterString(QString search, QString value);
    Q_INVOKABLE void filterStringColumn(QString tabName);
    Q_INVOKABLE int getColumnCount();
    Q_INVOKABLE QList<QString> getDataComboBox();
    Q_INVOKABLE QList<QString> getDataComboBoxInt();
    Q_INVOKABLE QList<QString> getColorFilter();
    Q_INVOKABLE void addTag(QString name, QString value);
    Q_INVOKABLE void addTag1(QString name, QString value);
    Q_INVOKABLE void addTag2(QString name, int value1, int value2);
    Q_INVOKABLE void addTag3(QString name, int value, QString mark);
    Q_INVOKABLE void removeTag(QString filterSearch, QString name, QString value);

    Q_INVOKABLE void selectionRow(int Row, int Column);
    Q_INVOKABLE QItemSelectionModel *selectRowModel();

    //QStringList comboItem() const;
    //void setComboItem(const QStringList &newComboItem);

    //QStringList comboItemList() const;
    //void setComboItemList(const QStringList &newComboItemList);

    Q_INVOKABLE QList<QString> getTabBarName();

    Q_INVOKABLE QStringList filterCombo(QString text, QString nameFilter);

    Q_INVOKABLE void attacker(QString name);

signals:
    //void comboItemChanged();

    //void comboItemListChanged();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;


private:
    //QString m_filterColor;
    QString m_filterName;
    QString m_filterColumn;
    //int m_filterFrom;
    //int m_filterTo;
    //QString m_condition;
    QString m_searchTextCombo;

    QString m_search = ""; //filter check
    bool Asc = true; //ascending or descending sort
    MyTableView myTableModel;


    QVector<QString> columnName;
    QVector<QString> columnNameInt;
    QVector<QString> colorList;
    QVector<QString> tabList;

    QVector<QString> comboSearch;
    //QStringList m_comboItem;
    //QStringList m_comboItemList;

    QList<FilterTag> Tags;
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

#endif // MYPROXYMODEL_H
